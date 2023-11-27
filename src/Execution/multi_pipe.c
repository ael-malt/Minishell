/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/27 15:46:42 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

void	multi_pipe(t_lst *lst, t_expand *ex)
{
	int	fd[2];
	int	pid;
	int	fd_temp;
	int	status;
	int	here;
	
	fd_temp = 0;
	if (!lst)
		return ;
	// here = count_heredoc(lst); //soit heredoc avant commande = dup2 entree soit ya pas de commande et sans dup2
	while (lst)
	{
		// if (lst->token == 2 && is_heredoc(lst) == 1)
		// {
		// 	if (lst->next && lst->next->token == 1)
		// 		break ;
		// 	else
		// 		redirect(lst);
		// }
		if (lst->token == 0)
		{
			if (lst->next && ((lst->next->token == 1) || check_pipe_after_redir(lst))) // retiré (lst->token == 0 && ) du if
				if (pipe(fd) == -1)
					perror("Pipe");
			pid = fork();
			if (pid == -1)
				perror("FORK");
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				if (lst->token == 0 && ((lst->prev && lst->prev->token == 1)
					|| (lst->next && lst->next->token == 1)
					|| check_pipe_after_redir(lst)))
					{
						pipex(fd, &fd_temp, lst);
						// fprintf(stderr, "pipex %s\n", lst->command);
					}
				if (lst->next && lst->next->token == 2)
					redirect(lst);
				execute(lst, ex);
			}
			else
			{
				if (is_builtin(lst) && !lst_count_pipe(lst)) 
					builtin(lst, ex);
				if (lst->next && (lst->next->token == 1 || check_pipe_after_redir(lst))) 
				{
					if (fd_temp)
						close(fd_temp);
					fd_temp = dup(fd[0]);
					close(fd[0]);
					close(fd[1]);
				}
				// close(fd[0]);
				// close(fd[1]);
				waitpid(pid, &status, 0);
				g_exit_status = status / 256;
			}
		}
		lst = lst->next;
	}
}

void	input_heredoc(t_lst *lst, int file)
{
	// int	file;

	// file = 0;
	if (lst->prev && is_redir(lst->prev) == 1)
	{
		file = open_redir_file(lst->prev);
		fprintf(stderr, "input heredoc\n");
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	// if (file)
	// 	close(file);
}

void	redirex(int file, t_lst *lst)
{
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		// fprintf(stderr, "redirex STDOUT: %s\n", lst->command);
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 3 || (lst->next && is_redir(lst) == 1))//lst->next pour heredoc seul
	{
		// fprintf(stderr, "redirex STDIN: %s\n", lst->command);
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	fprintf(stderr, "file %d\n", file);
	if (file)
		close(file);
	if (lst->next && lst->next->token == 2 && is_redir(lst->next) > 1)
	{
		// fprintf(stderr, "redir dif\n");
		redirect(lst);
	}
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	
	// if (lst->next && lst->next->token == 1)
	if (lst->prev && lst->prev->token == 1)
	{
		// fprintf(stderr, "pipex STDIN: %s\n", lst->command);
		if (dup2(*fd_temp, STDIN_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}	
	close(fd[0]);
	if (lst->next && (lst->next->token == 1 || check_pipe_after_redir(lst)))
	{
		// fprintf(stderr, "pipex STDOUT: %s\n", lst->command);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}
	close(*fd_temp);
	close(fd[1]);
}

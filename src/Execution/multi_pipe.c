/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/12/04 19:49:38 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;
// heredoc d'affiler avant marche pas meme heredoc silp
// << hf << q ls > lk = resultat attendu mais imprime dans heredoc a la fin du dernier le doc ou on redirige < lk

void	multi_pipe(t_lst *lst, t_expand *ex)
{
	int	fd[2];
	int	pid;
	int	fd_temp;
	int	status;
	int file;
	t_lst *tmp;
	int	here;
	
	fd_temp = 0;
	file = 0;
	here = count_heredoc(lst);
	if (!lst)
		return ;
	if (here > 0)
	{
		tmp = lst;
		while (tmp && here)
		{
			if (is_redir(tmp) == 1)
			{
				mini_heredoc(tmp);
				here--;
			}
			tmp = tmp->next;
		}
	}
	while (lst)
	{
		if (only_redir(lst) == lstsize(lst))
			ft_open(lst);
		if (lst->token == 0)
		{
			if (lst->next && ((lst->next->token == 1) || check_pipe_after_redir(lst)))
				if (pipe(fd) == -1)
					perror("Pipe");
			pid = fork();
			if (pid == -1)
				perror("FORK");
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				if (lst->token == 0 && lst->next == NULL && lst->prev && lst->prev->token == 2)
						input_command(lst, file);
					if (lst->token == 0 && ((lst->prev && lst->prev->token == 1)
						|| (lst->next && lst->next->token == 1)
						|| check_pipe_after_redir(lst)))
							pipex(fd, &fd_temp, lst);
					if (lst->next && lst->next->token == 2)
						redirect(lst);
					execute(lst, ex);
			}
			else
			{
				if (is_builtin(lst) && !lst_count_pipe(lst) && !lst_count_redir(lst) && !lst->next && !lst->prev) 
				{
					builtin(lst, ex);
				}
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

void	redirex(int file, t_lst *lst)
{
	// fprintf(stderr, "av0 .dup %s\n", lst->command);
	if ((is_redir(lst) == 2 || 	is_redir(lst) == 4))
	{
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 3 || (is_redir(lst) == 1))
	{
		// if (is_redir(lst) == 1)
		// {
		// 	file = open(".tmp", O_RDWR, 0644);
		// 	if (file < 0)
		// 		ft_perror("open");
		// }
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
		// fprintf(stderr, "coucouc\n");
	}
	if (file)
		close(file);
	if (lst->next && lst->next->token == 2 && is_redir(lst->next) > 1)
		redirect(lst);
	// fprintf(stderr, "coucouc\n");
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	// int	file;
	// int	flag;

	// file = 0;
	// flag = 0;
	// printf("pipex : %s %d %d\n", lst->command, lst->token, file);
	// if (lst->prev && lst->prev->token == 2)
	// {
	// 	input_command(lst, file);
	// 	flag = 1;
	// }
	if (lst->prev && lst->prev->token == 1 /*&& flag == 0*/)
	{
		// fprintf(stderr, "pipex STDIN: %s\n", lst->command);
		// fprintf(stderr, "cat\n");
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

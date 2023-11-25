/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/25 15:04:55 by lazanett         ###   ########.fr       */
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
	
	fd_temp = 0;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->token == 0)
		{
			if (lst->next && lst->next->token == 1) // retiré (lst->token == 0 && ) du if
				if (pipe(fd) == -1)
					perror("Pipe");
			pid = fork();
			if (pid == -1)
				perror("FORK");
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				if ((lst->prev && lst->prev->token == 1) || (lst->next && lst->next->token == 1))
					pipex(fd, &fd_temp, lst);
				if (lst->next && lst->next->token == 2)
					redirect(lst);
				execute(lst, ex);
			}
			else
			{
				if (is_builtin(lst) && !lst_count_pipe(lst)) 
					builtin(lst, ex);
				if (lst->next && lst->next->token == 1) {
					if (fd_temp) {
						close(fd_temp);
					}
					fd_temp = dup(fd[0]);
					close(fd[0]);
					close(fd[1]);
				}
				close(fd[0]);
				close(fd[1]);
				waitpid(pid, &status, 0);
				g_exit_status = status / 256;
			}
		}
		// printf("ffgff\n");
		// is_solo_heredoc(lst, fd_temp);
		if (lst->token == 2 && is_redir(lst) == 1 && lst->prev == NULL && lst->next == NULL) // heredox seul
			redirect(lst);
		lst = lst->next;
	}
}

// void	is_solo_heredoc(t_lst *lst, int fd_temp) // fonctione pas car message erreur fin heredoc
// {
// 	if (lst->token == 2 && is_redir(lst) == 1 && lst->prev == NULL && lst->next == NULL)
// 	{
// 		redirect(lst, fd_temp);
// 	}
// }

void	redirex(int file, t_lst *lst)
{
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		fprintf(stderr, "is_redir %s\n", lst->command);
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 3 || (lst->next && is_redir(lst) == 1))//lst->next pour heredoc seul
	{
		fprintf(stderr, "std in = file\n");
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	if (file)
		close(file);
	if (lst->next && lst->next->token == 2)
	{
		fprintf(stderr, "redir dif\n");;
		redirect(lst);
	}
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	if (dup2(*fd_temp, STDIN_FILENO) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return ;
	}
	close(fd[0]);
	if (lst->next && lst->next->token == 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}
	close(*fd_temp);
	close(fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/22 18:39:38 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

// TO-DO
// Ajouter < et << au redirections multipipes
// Gerer les redirections en dernier maillon
// Refaire mon heardoc

void	execute(t_lst *lst, t_expand *ex)
{
	if (is_builtin(lst) && lst_count_pipe(lst))
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (is_builtin(lst))
		exit(0);
	else if (!is_builtin(lst) &&ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else if (!is_builtin(lst))
		excecuting(lst, ex->tab);
}

void redirect(t_lst *lst, int fd_temp)
{	
	int	file;

	if (lst->next)
		lst = lst->next;

	file = open_redir_file(lst);
	if (file < 0)
		return (exit(0));
	while (lst->next && is_redir(lst->next) && (is_redir(lst) == is_redir(lst->next) || is_redir(lst) == (is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
			return (exit(0));
	}
	// // printf("rex: %s %d %d\n", lst->command, lst->token, file);
	redirex(file, &fd_temp, lst);
}

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
				// fprintf(stderr, "cmd: %s token: %d next: %d next_token: %d\n", lst->command ? lst->command : "no", lst->token, lst->next ? 1 : 0, lst->next ? lst->next->token : -1);
				if ((lst->prev && lst->prev->token == 1) || (lst->next && lst->next->token == 1))
				{
					// fprintf(stderr, "pipex\n");
					pipex(fd, &fd_temp, lst);
					// ft_printf("ici\n");

				}
				if (lst->next && lst->next->token == 2)
				{
					// fprintf(stderr, "command: %s\n", lst->command);
					// fprintf(stderr, "redirect\n");
					redirect(lst, fd_temp);
				}
				// fprintf(stderr, "execute %s %d\n", lst->command, fd_temp);
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
				waitpid(pid, &status, 0);
				g_exit_status = status / 256;
			}
		}
		lst = lst->next;
	}
}

void	redirex(int file, int *fd_temp, t_lst *lst)
{
	(void) fd_temp;
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 1 || is_redir(lst) == 3)
	{
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	if (file)
		close(file);
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	// fprintf(stderr, "command: %s\n", lst->command);

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

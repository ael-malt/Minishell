/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/15 17:55:29 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TO-DO
// Ajouter < et << au redirections multipipes
// Gerer les redirections en dernier maillon
// Refaire mon heardoc

void	multi_pipe(t_lst *lst, t_expand *ex)
{
	int	i;
	int	nb_operator;
	int	fd[2];
	int	fd_temp;

	i = 0;
	fd_temp = 0;
	nb_operator = lst_count_pipe(lst) + lst_count_redir(lst);
	while (i <= nb_operator)
	{
		if (i < (nb_operator))
		{
			if (lst->next && lst->token != 2 && lst->next->token == 1)
			{
				pipex(fd, &fd_temp, lst, ex);
				if (lst->next != NULL && lst->next->next != NULL)
					lst = lst->next->next;
			}
			else if (lst->next && (lst->next->token == 2 || lst->token == 2))
			{
				redirex(&fd_temp, lst, ex);
				if (lst->next && lst->next->token == 0 && lst->next->next 
					&& lst->next->next->token == 1 && lst->next->next->next)
					lst = lst->next->next->next;
				else if (lst->next && lst->next->next && \
				(lst->next->token == 0 || lst->next->token == 1))
					lst = lst->next->next;
				else if (lst->next)
					lst = lst->next;
			}
		}
		else
		{
			if (get_last_operator(lst) == 1)
				last_pipe(fd, &fd_temp, lst, ex);
			// else if (get_last_operator(lst) == 2)
			// 	last_redir(fd, &fd_temp, lst, ex);
		}
		i++;
	}
	wait(NULL);
}

void	redirex(int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;
	int file;

	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
	{
		file = open_redir_file(lst);
		if ((is_redir(lst) == 2 || is_redir(lst) == 4))
			redir_out(*fd_temp, lst, ex, file);
		else if (is_redir(lst->next) == 2 || is_redir(lst->next) == 4)
			redir_out(*fd_temp, lst, ex, file);
		else if (is_redir(lst) == 3)
			redir_in(*fd_temp, lst, ex, file);
		else if (is_redir(lst->next) == 3)
			redir_in(*fd_temp, lst->next, ex, file);
		if (file)
			close(file);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}

// void	exc_redir(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	if (dup2(fd_temp, STDIN_FILENO) == -1)
// 		ft_perror("Dup");
// 	close(fd[0]);
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		perror("Dup");
// 	close(fd_temp);
// 	close(fd[1]);
// 	if (is_builtin(lst))
// 	{
// 		builtin(lst, ex);
// 		exit(0);
// 	}
// 	else if (ft_strchr(lst->split_command[0], '/') != NULL)
// 		exc_absolut_way(lst, ex);
// 	else
// 		excecuting(lst, ex->tab);
// }

void	pipex(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;

	if (pipe(fd) == -1)
		perror("Pipe");
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
		exc_cmd(fd, *fd_temp, lst, ex);
	else
	{
		if (*fd_temp)
			close(*fd_temp);
		*fd_temp = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	exc_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
		ft_perror("Dup");
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("Dup");
	close(fd_temp);
	close(fd[1]);
	if (is_builtin(lst))
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else
		excecuting(lst, ex->tab);
}



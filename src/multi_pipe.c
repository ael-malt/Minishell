/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/14 18:20:08 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TO-DO
// Ajouter < et << au redirections multipipes
// Gerer les redirections en dernier maillon
// Refaire mon heardoc
int	lst_count_pipe(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 1)
			count++;
		lst = lst->next;
	}
	return (count);
}

int lst_count_redir(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 2)
			count++;
		lst = lst->next;
	}
	return (count);
}
int	len_lst(t_lst *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
int	get_last_operator(t_lst *lst)
{
	int	operator;

	operator = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 1)
			operator = 1;
		else if (lst->token == 2)
			operator = 2;
		lst = lst->next;
	}
	return (operator);
}
void	multi_pipe(t_lst * lst, t_expand *ex)
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
				// ft_printf("\n\nlst->content: %s\n\n", lst->command);
			if (lst->next && lst->token != 2 && lst->next->token == 1)
			{
				pipex(fd, &fd_temp, lst, ex);
				if (lst->next != NULL && lst->next->next != NULL)
					lst = lst->next->next;
			}
			else if (lst->next && (lst->next->token == 2 || lst->token == 2))
			{
				// printf("here");
				redirex(fd, &fd_temp, lst, ex);
				// if (lst->next != NULL && lst->next->next != NULL)
				if(lst->next && lst->next->token == 0 && lst->next->next && lst->next->next->token == 1 && lst->next->next->next)
					lst = lst->next->next->next;
				else if (lst->next && lst->next->next && (lst->next->token == 0 || lst->next->token == 1))
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

int	open_redir_file(t_lst *lst)
{
	int	file;
	
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		if (is_redir(lst) == 2)
			file = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (is_redir(lst) == 4)
			file = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if  (is_redir(lst->next) == 2 || is_redir(lst->next) == 4)
	{
		if (is_redir(lst->next) == 2)
			file = open(lst->next->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (is_redir(lst->next) == 4)
			file = open(lst->next->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);

	}
	else if (is_redir(lst) == 3)
		file = open(lst->split_redir[1], O_RDONLY, 0644);
	else if (is_redir(lst->next) == 3)
		file = open(lst->next->split_redir[1], O_RDONLY, 0644);

	if (file < 0)
		perror("File");
	return (file);
}

void redirex(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;
	int file;
	// ft_printf("here\n");

	// (void) fd;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
	{
		file = open_redir_file(lst);
		if ((is_redir(lst) == 2 || is_redir(lst) == 4))
			redir_out(fd, *fd_temp, lst, ex, file);
		else if  (is_redir(lst->next) == 2 || is_redir(lst->next) == 4)
			redir_out(fd, *fd_temp, lst, ex, file);
		else if (is_redir(lst) == 3)
			redir_in(fd, *fd_temp, lst, ex, file);
		else if (is_redir(lst->next) == 3)
			redir_in(fd, *fd_temp, lst->next, ex, file);
		if (file)
			close(file);
		// else if(is_solo_redir(lst) == 1 && is_redir(lst) == 3)
		// 	solo_redir_in(lst, ex);
	}
	else
	{
		//parent
		// if (*fd_temp)
		// 	close(*fd_temp);
		// *fd_temp = dup(fd[0]);
		close(fd[0]);
		close(fd[1]); //nouveau
		waitpid(pid, NULL, 0); // ?
	}
}

// void	last_redir(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
// {
// 	int	pid;

// 	// if (pipe(fd) == -1)
// 	// 	perror("Pipe")x;
// 	pid = fork();
// 	if (pid < 0)
// 		perror("FORK");
// 	if (pid == 0)
// 	{
// 		//child
// 		exc_last_cmd(fd, *fd_temp, lst, ex);
// 	}
// 	else
// 	{
// 		if (*fd_temp)
// 			close(*fd_temp);
// 		close(fd[0]);
// 		waitpid(pid, NULL, 0);
// 	}
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
	{
		exc_cmd(fd, *fd_temp, lst, ex);
	}
	else
	{
		if (*fd_temp)
			close(*fd_temp);
		*fd_temp = dup(fd[0]);
		close(fd[0]);
		close(fd[1]); //nouveau
		waitpid(pid, NULL, 0); // ?
	}
}


void	last_pipe(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;

	// if (pipe(fd) == -1)
	// 	perror("Pipe");
	pid = fork();
	if (pid < 0)
		perror("FORK");
	if (pid == 0)
	{
		//child
		exc_last_cmd(fd, *fd_temp, lst, ex);
	}
	else
	{
		if (*fd_temp)
			close(*fd_temp);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	exc_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd_temp, STDIN_FILENO) == -1) //FD_TEMP car on recup du pipe pres
		ft_perror("Dup");
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1) // ecrit dans le pipe
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

void	exc_last_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd_temp, STDIN_FILENO) == -1) // pipe pres
		perror("Dup");
	(void) fd;
	// close(fd[0]);
	// if (dup2(fd[1], STDOUT_FILENO) == -1) // si pas redir
	// 	perror("Dup");
	// close(fd[1]);
	close(fd_temp);
	if (is_builtin(lst))
	{
		builtin(lst, ex);
		exit(0);
	}
	if (ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else
		excecuting(lst, ex->tab);
}

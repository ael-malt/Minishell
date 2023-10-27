/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/27 14:39:31 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	multi_pipe(t_lst * lst, t_expand *ex)
{
	int	i;
	int	nb_pipe;
	int	fd[2];
	int	fd_temp;

	i = 0;
	fd_temp = 0;
	nb_pipe = lst_count_pipe(lst);

	while (i <= nb_pipe)
	{
		if (i < (nb_pipe))
		{
			pipex(fd, &fd_temp, lst, ex);
			if (lst->next != NULL && lst->next->next != NULL)
				lst = lst->next->next;
		}
		else
			last_pipe(fd, &fd_temp, lst, ex);
		i++;
	}
	wait(NULL);
}
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
		//child
		exc_cmd(fd, *fd_temp, lst, ex);
	}
	else
	{
		//parent
		if (*fd_temp)
			close(*fd_temp);
		*fd_temp = dup(fd[0]);
		close(fd[0]);
		close(fd[1]); //nouveau
		// waitpid(pid, NULL, 0);
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
	if (is_builtin(lst) == 1)
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst);
	else
		excecuting(lst, ex->tab);
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
		//parent
		if (*fd_temp) //NOUVEAU
			close(*fd_temp);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
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
	if (is_builtin(lst) == 1)
	{
		builtin(lst, ex);
		exit(0);
	}
	if (ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst);
	else
		excecuting(lst, ex->tab);
}

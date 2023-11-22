/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:51:49 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/15 16:52:13 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	last_pipe(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("FORK");
	if (pid == 0)
		exc_last_cmd(fd, *fd_temp, lst, ex);
	else
	{
		if (*fd_temp)
			close(*fd_temp);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	exc_last_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
		perror("Dup");
	(void) fd;
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

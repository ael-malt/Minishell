/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:52:28 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/15 18:00:01 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	last_redir(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("FORK");
	if (pid == 0)
		exc_last_redir(fd, *fd_temp, lst, ex);
	else
	{
		if (*fd_temp)
			close(*fd_temp);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	exc_last_redir(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	int	file;

	signal(SIGQUIT, SIG_DFL);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
		perror("Dup");
	(void) fd;
	close(fd_temp);
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

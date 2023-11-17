/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:48:16 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/17 18:01:43 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

void	redir_in(int fd_temp, t_lst *lst, t_expand *ex, int infile)
{
	t_lst *tmp_lst;

	signal(SIGQUIT, SIG_DFL);
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	if (dup2(fd_temp, STDOUT_FILENO) == -1)
		ft_perror("Dup");
	close(fd_temp);
	// if (dup2(STDOUT_FILENO, fd_temp) == -1)
	// 	perror("Dup");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror("Dup");
	if (tmp_lst && is_builtin(tmp_lst) == 1)
	{
		builtin(tmp_lst, ex);
		exit(0);
	}
	else if (tmp_lst && ft_strchr(tmp_lst->next->split_command[0], '/') != NULL)
		exc_absolut_way(tmp_lst, ex);
	else if (tmp_lst)
		excecuting(tmp_lst, ex->tab);
}

void	solo_redir_in(t_lst *lst, t_expand *ex, int infile)
{
	int	pid;
	int	status;
	int fd[2];
	t_lst *tmp_lst;

	(void) fd;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_perror("Dup");
		if (ft_strchr(tmp_lst->split_command[0], '/') != NULL && !is_builtin(tmp_lst))
			exc_absolut_way(tmp_lst, ex);
		else if (!is_builtin(tmp_lst))
			excecuting(tmp_lst, ex->tab);
	}
	else
	{
		if (is_builtin(tmp_lst))
			builtin(tmp_lst, ex);
		//waitpid(pid, NULL, 0);
		//if (WEXITSTATUS(pid) > 0
		//close(fd[0]);
		// close(fd[1]);
		waitpid(pid, &status, 0);
		// Utilisez la macro WEXITSTATUS pour obtenir la valeur de retour
		//if (WIFEXITED(status))
		//printf("%d\n", status);
		g_exit_status = status / 256;
		//printf("%d\n", g_exit_status);
	}
	//printf("var globale = %d\n", g_exit_status);
}

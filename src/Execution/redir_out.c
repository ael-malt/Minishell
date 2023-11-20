/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:29 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/20 13:54:03 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

void	redir_out(int fd_temp, t_lst *lst, t_expand *ex, int outfile)
{
	t_lst	*tmp_lst;

	signal(SIGQUIT, SIG_DFL);
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	// ft_printf("content: %s\n", tmp_lst->content);
	// if (dup2(fd_temp, STDIN_FILENO) == -1)
	// 	ft_perror("Dup");
	// close(fd[0]);
	close(fd_temp);
	// close(fd[1]);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror("Dup");
	if (tmp_lst && is_builtin(tmp_lst) == 1)
	{
		builtin(tmp_lst, ex);
		exit(0);
	}
	else if (tmp_lst && ft_strchr(tmp_lst->split_command[0], '/') != NULL)
		exc_absolut_way(tmp_lst, ex);
	else if (tmp_lst)
		excecuting(tmp_lst, ex->tab);
}

void	solo_redir_out(t_lst *lst, t_expand *ex, int outfile)
{	
	int		pid;
	int		status;
	int 	fd[2];
	t_lst	*tmp_lst;
	
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
		if (dup2(outfile, STDOUT_FILENO) == -1)
			perror("Dup");
		if (ft_strchr(tmp_lst->split_command[0], '/') != NULL && !is_builtin(lst))
			exc_absolut_way(tmp_lst, ex);
		else if (!is_builtin(lst))
			excecuting(tmp_lst, ex->tab);
	}
	else
	{
		if (is_builtin(lst))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/28 14:39:02 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_redir(t_lst *lst)
{
	if (!lst)
		return(-1);
	if (is_heredoc(lst) == 1)
		return (1);
	else if (lst->token == 2 && lst->command[0] == '>' && lst->command[1] == '>')
		return (4);
	else if (lst->token == 2 && lst->command[0] == '>')
		return (2);
	else if (lst->token == 2 && lst->command[0] == '<')
		return (3);
	return (0);
}

int	open_redir_file(t_lst *lst)
{
	int	fd;

	fd = 0;
	fd = 0;
	if (is_redir(lst) == 2)
		fd = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(lst) == 4)
		fd = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_redir(lst) == 3)
		fd = open(lst->split_redir[1], O_RDONLY, 0644);
	else if (is_redir(lst) == 1)
		fd = mini_heredoc(lst);
	if (fd < 0)
		mini_perror(NDIR, lst->split_redir[1], 1);
	return (fd);
}

void redirect(t_lst *lst)
{	
	int	file;

	file = 0;
	if (lst->prev && lst->prev->token == 2)
		input_command(lst, file);
	if (lst->next)
		lst = lst->next;
	file = open_redir_file(lst);
	if (file < 0)
		return (exit(0));
	while (lst->next && is_redir(lst->next) && is_redir(lst->next) > 1 && \
		(is_redir(lst) == is_redir(lst->next) || is_redir(lst) == \
		(is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		if (file > 0)
				close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
			return (exit(0));
	}
	redirex(file, lst);
}

int	check_pipe_after_redir(t_lst *lst)
{
	t_lst	*tmp_lst;

	tmp_lst = 0;
	if ((!lst->prev && !lst->next) || (lst->next && !lst->command) || \
		!lst_count_pipe(lst))
		return (0);
	if ((lst->next && lst->next->command && lst->token == 0))
	if ((lst->next && lst->next->command && lst->token == 0))
		tmp_lst = lst->next;
	// ft_printf("tmp lst cmd: %s\n",tmp_lst->next->command);
	while (tmp_lst->next && is_redir(tmp_lst))
	{
	{
		tmp_lst = tmp_lst->next;
	}
	}
	if (tmp_lst->token == 1 && is_redir(tmp_lst->prev))
		return (1);
	return (0);
}


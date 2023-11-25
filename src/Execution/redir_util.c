/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/25 15:54:26 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_solo_redir(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->token == 2)
			count++;
		lst = lst->next;
	}
	return (count);
}

int	is_redir(t_lst *lst)
{
	if (!lst)
		return(-1);
	if (is_heredoc(lst) == 1) // heredoc <<
		return (1);
	else if (lst->token == 2 && lst->command[0] == '>' && lst->command[1] == '>') //ajout append >>
		return (4);
	else if (lst->token == 2 && lst->command[0] == '>') // sortie
		return (2);
	else if (lst->token == 2 && lst->command[0] == '<') // entree
		return (3);
	return (0);
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

int	open_redir_file(t_lst *lst)
{
	int	fd;

	if (is_redir(lst) == 2)
		fd = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(lst) == 4)
		fd = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_redir(lst) == 3)
		fd = open(lst->split_redir[1], O_RDONLY, 0644);
	else if (is_redir(lst) == 1)
		mini_heredoc(lst);
	if (fd < 0)
		mini_perror(NDIR, lst->split_redir[1], 1);
	return (fd);
}

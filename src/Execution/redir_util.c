/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/20 16:10:20 by ael-malt         ###   ########.fr       */
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

	// while (lst->next && (is_redir(lst->next) == 2 || is_redir(lst->next) == 4))
	// {
	// 	if (is_redir(lst) == 2 )
	// 		fd = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	else if (is_redir(lst) == 4)
	// 		fd = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	// 	close (fd);
	// 	lst = lst->next;
	// }
	// while (lst->next && is_redir(lst->next) == 3)
	// {
	// 	fd = open(lst->split_redir[1], O_RDONLY, 0644);
	// 	close (fd);
	// 	lst = lst->next;
	// }
	if (is_redir(lst) == 2)
		fd = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(lst) == 4)
		fd = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_redir(lst) == 3)
		fd = open(lst->split_redir[1], O_RDONLY, 0644);
	if (fd < 0)
		perror("fd");
	return (fd);
}

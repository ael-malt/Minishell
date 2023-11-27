/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/27 15:40:16 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		mini_heredoc(lst);
	if (fd < 0)
		mini_perror(NDIR, lst->split_redir[1], 1);
	return (fd);
}

void redirect(t_lst *lst)
{	
	int	file;

	file = 0;
	
	if (lst->next)
		lst = lst->next;
	// fprintf(stderr, "passe dans redirect %s\n", lst->command);
	file = open_redir_file(lst);
	if (file < 0)
	{
		// fprintf(stderr, "file < 0\n");
		return (exit(0));
	}
	while (lst->next && is_redir(lst->next) && is_redir(lst->next) > 1 && (is_redir(lst) == is_redir(lst->next) || is_redir(lst) == (is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
		{
			// fprintf(stderr, "file < 0\n");
			return (exit(0));
		}
	}
	// printf("rex: %s %d %d\n", lst->command, lst->token, file);
	// input_heredoc(lst, file);
	// if (is_redir(lst) > 1)
	redirex(file, lst);

}

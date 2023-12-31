/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:46:05 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/04 18:17:54 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void	heredoc_in_redir(t_lst *lst);
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
	if (is_redir(lst) == 2)
		fd = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(lst) == 4)
		fd = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (is_redir(lst) == 3)
		fd = open(lst->split_redir[1], O_RDONLY, 0644);
	else if (is_redir(lst) == 1)
		fd = open(".tmp", O_RDONLY, 0644);
	if (fd < 0)
		mini_perror(NDIR, lst->split_redir[1], 1);
	return (fd);
}

void redirect(t_lst *lst)
{	
	int	file;

	file = 0;
	if (lst->prev && lst->prev->token == 2)// avant commande
		input_command(lst, file);
	// fprintf(stderr, "%s\n", lst->command);
	if (lst->next && lst->next->token == 2) // ajout du token
		lst = lst->next;
	file = open_redir_file(lst);
	if (file < 0)
		return (exit(0)); //si exit = allocation non free
	while (lst->next && is_redir(lst->next) && is_redir(lst->next) > 1 && \
		(is_redir(lst) == is_redir(lst->next) || is_redir(lst) == \
		(is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		// fprintf(stderr, " boucle %s\n", lst->command);
		if (file < 0)
			close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
			return (exit(0));
	}
	// fprintf(stderr, "%s\n", lst->command);
	// if (lst->next && is_redir(lst->next) == 1)// heredoc apres commande
	// 	heredoc_in_redir(lst); 
	redirex(file, lst);
}

void	heredoc_in_redir(t_lst *lst)
{
	int	file;

	file = 0;
	while (lst->next && is_redir(lst->next) == 1)
	{
		// fprintf(stderr, "%s\n", lst->command);
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

void	input_command(t_lst *lst, int file)
{
	while (lst->prev != NULL && lst->prev->token == 2)
		lst = lst->prev;
	file = open_redir_file(lst);
	if (file < 0)
		return (exit(0));
	while (lst->next && lst->next->token == 2)
	{
		close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
			return (exit(0));
	}
	redirex(file, lst);
}

int	only_redir(t_lst *lst)
{
	t_lst	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	if (!tmp)
		return (-1);
	while (tmp)
	{
		if (tmp->token == 2)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	lstsize(t_lst *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	ft_open(t_lst * lst)
{
	t_lst	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->token == 2)
			open_redir_file(lst);
		tmp = tmp->next;
	}
	// while (tmp->prev)
	// 	tmp = tmp->prev;
	// printf("count %d size %d\n", count, lstsize(tmp));
	// if (lstsize(tmp) == count)
	// 	return (1);
	// return (0);
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


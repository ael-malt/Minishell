/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_supp_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:56:49 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/09 16:56:49 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	search_quote_in_split_command(t_lst *lst)
{
	int	i;
	int	len;
	int	index;
	int	flag;

	len = 0;
	index = 0;
	flag = 0;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->token == 0)
		{
			i = 0;
			while (lst->split_command[i])
			{
				if (is_quote(lst->split_command[i]) == 1)
					lst->split_command[i] = supp_quote(lst->split_command[i], \
					len, index, flag);
				i++;
			}
		}
		lst = lst->next;
	}
}

void	search_quote_in_split_redir(t_lst *lst)
{
	int	len;
	int	index;
	int	flag;

	len = 0;
	index = 0;
	flag = 0;
	if (!lst || check_is_name_for_redir(lst) != 0)
		return ;
	while (lst)
	{
		if (lst->token == 2)
		{
			if (is_quote(lst->split_redir[1]) == 1)
				lst->split_redir[1] = supp_quote(lst->split_redir[1], \
				len, index, flag);
		}
		lst = lst->next;
	}
}

char	*supp_quote(char *s, int len, int index, int flag)
{
	int		i;
	char	search;
	char	*rep;

	rep = NULL;
	rep = malloc_char_supp_quotte(len, rep, s);
	i = 0;
	while (s[i])
	{
		while (s[i] && flag == 1 && search == s[i])
			i++;
		if (flag == 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			search = s[i];
			while (s[i] && search == s[i])
				i++;
			flag = 1;
		}
		rep[index] = s[i];
		if (s[i])
			i++;
		index++;
	}
	rep[index] = '\0';
	return (rep);
}

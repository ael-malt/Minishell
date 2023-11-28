/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_lst_len_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:01:52 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/28 12:06:33 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tab_command(t_lst *lst, t_split *sp)
{
	// int	i;

	// i = 0;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->token == 0)
			lst->split_command = assign_tab_command(lst->command, lst, sp);
		else if (lst->token == 2)
			lst->split_redir = ft_split_redir(lst->command, " \t\n", sp);
		lst = lst->next;
	}
}

//a surveiller i =-1 et ++i
int	len_tab_command(char *s)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s && s[++i] != '\0')
	{
		if (s[i] != '\0' && s[i] == '\'')
		{
			i = search_next_word_simple_quote(s, i);
			count++;
		}
		else if (s[i] != '\0' && s[i] == '\"')
		{
			i = search_next_word_double_quote(s, i);
			count++;
		}
		else if (s[i] != '\0' && s[i] != '\"' && s[i] != '\'' && s[i] != ' ' \
			&& s[i] != '\t')
		{
			i = search_next_word(s, i);
			count++;
		}
	}
	return (count);
}

int	search_next_word(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	i = i - 1;
	return (i);
}

int	search_next_word_simple_quote(char *s, int i)
{
	i++;
	while (s[i] && s[i] != '\'')
		i++;
	while (s[i] && (s[i] != ' ' && s[i] != '\t'))
		i++;
	i = i - 1;
	return (i);
}

int	search_next_word_double_quote(char *s, int i)
{
	i++;
	while (s[i] && s[i] != '\"')
		i++;
	while (s[i] && (s[i] != ' ' && s[i] != '\t'))
		i++;
	i = i - 1;
	return (i);
}

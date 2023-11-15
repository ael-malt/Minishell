/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_supp_quotte_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:08:23 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/14 17:08:23 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_quote(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (-1);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*malloc_char_supp_quotte(int len, char *rep, char *s)
{
	while (s[len])
		len++;
	rep = malloc(sizeof (char) * len + 1);
	if (!rep)
		return (NULL);
	return (rep);
}

int	check_is_name_for_redir(t_lst *lst)
{
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->token == 2)
		{
			if (lst->split_redir[1] == NULL)
			{
				mini_heardoc_error(NONAME, "", 2);
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}

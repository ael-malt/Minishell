/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_first_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/16 14:53:38 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_double_pipe(t_lst *lst)
{
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next != NULL)
	{
		if (lst->token == 1 && lst->next->token == 1)
		{
			mini_perror2(OPERROR, *lst->next->command, 2);
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	check_last_is_pipe(t_lst *lst)
{
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->next == NULL && lst->token == 1)
		{
			mini_heardoc_error(SYNTAX, "", 2);
			return (1);
		}
		lst = lst->next;
	}
	return(0);
}
int	search_char(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' || s[i] == ';')
			return (1);
		i++;
	}
	return (0);
}


int	search_quote(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (flag == 0 && s[i] == '\'')
			flag = 1;
		else if (flag == 1 && s[i] == '\'')
			flag = 3;
		else if (flag == 0 && s[i] == '\"')
			flag = 2;
		else if (flag == 2 && s[i] == '\"')
			flag = 0;
		i++;
	}
	if (flag != 0)
		return (1);
	return (0);
}

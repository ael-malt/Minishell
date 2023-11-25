/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:58:39 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/25 11:48:58 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	lst_count_pipe(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 1)
			count++;
		lst = lst->next;
	}
	return (count);
}

int	len_lst(t_lst *lst)
{
	int	len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int	get_last_operator(t_lst *lst)
{
	int	operator;

	operator = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 1)
			operator = 1;
		else if (lst->token == 2)
			operator = 2;
		lst = lst->next;
	}
	return (operator);
}

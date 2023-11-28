/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_operator_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:59:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/09 12:59:08 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	assign_token(t_lst *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->command && lst->command[0] == '|')
			lst->token = 1;
		else if (lst->command
			&& (lst->command[0] == '>' || lst->command[0] == '<'))
			lst->token = 2;
		else
			lst->token = 0;
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	res_is_operator(t_lst *lst, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_operator(s[i]))
			count++;
		i++;
	}
	if (lst->len_command_total == count)
		return (1);
	return (0);
}

int	len_operator(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst->content[i] && is_operator(lst->content[i]) == 1)
		i++;
	if (!error_operator_return(i, lst->content))
		return (i);
	else
		return (-1);
}

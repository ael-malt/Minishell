/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/14 14:58:03 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	last_quote(char *s, char search)
// {
// 	int	i;
// 	int index;

// 	i = 0;
// 	index = 0;
// 	while(s[i])
// 	{
// 		if (s[i] == search)
// 			index = i;
// 		i++;
// 	}
// 	return (index);
// }

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
			mini_perror2(OPERROR, *lst->next->command, 2); // 2 command npot found
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

// int	check_syntax(t_lst *lst)
// {
// 	if (!lst)
// 		return (-1);
// 	while (lst->prev)
// 		lst = lst->prev;
// 	while (lst)
// 	{
// 		if ((lst->token == 2 && lst->next->token == 1) || (lst->token == 1 && lst->next->token == 2))
// 		{
// 			mini_heardoc_error(SYNTAX, "", 2);
// 			return (1);
// 		}
// 		lst = lst->next;
// 	}
// 	return(0);
// }

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
// int	search_char(char *s) // chercher ';' et '\'
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\\' || s[i] == ';')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	search_quote(char *s) // check des guillements
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	while (s[i])
// 	{
// 		// Si c'est une SQUOTE
// 		if (flag == 0 && s[i] == '\'')// C'est l'ouvrante
// 			flag = 1;
// 		else if (flag == 1 && s[i] == '\'')// c'est la fermante
// 			flag = 3;
// 		// Si c'est une DQUOTE
// 		else if (flag == 0 && s[i] == '\"')// C'est l'ouvrante
// 			flag = 2;
// 		else if (flag == 2 && s[i] == '\"')// c'est la fermante
// 			flag = 0;
// 		i++;
// 	}
// 	//printf("%d = flag\n", flag);
// 	if (flag != 0)
// 		return (1);
// 	return (0);
// }

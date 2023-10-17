/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/17 14:59:27 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	search_quote_in_split(t_lst *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while(lst)
	{
		if (lst->token == 0)
		{
			while (lst->split_command[i])
			{
				printf("av = %s  || ", lst->split_command[i]);
				if (lst->split_command[i][0] == '\"' || lst->split_command[i][0] == '\'')
					lst->split_command[i] = supp_quote(lst->split_command[i]);
				printf("ap = %s %p\n", lst->split_command[i], lst->next);
				i++;
			}
		}
		lst = lst->next;
		i = 0;
	}
}

char	*supp_quote(char *s)
{
	int	i;
	int	index;
	int	len;
	char *rep;

	len = 0;
	index = 0;
	while (s[len])
		len++;
	rep = malloc(sizeof (char) * len + 1);
	if (!rep)
		return (NULL);
	i = 0;
	while (s[i]) // car len == " '"
	{
		if ((i == (len - 1) && s[i] == '\'') || (i == (len - 1) && s[i] == '\"'))
		{
			i++;
			if (s[i] == '\0')
				break;
		}
		if ((i == 0 && s[i] == '\'') || (i == 0 && s[i] == '\"'))
			i++;
		rep[index] = s[i];
		i++;
		index++;
	}
	rep[index] = '\0';
	return (rep);
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
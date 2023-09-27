/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/25 10:30:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_char(char *s) // chercher ';' et '\'
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

int	search_quote(char *s) // check des guillements
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		// Si c'est une SQUOTE
		if (flag == 0 && s[i] == '\'')// C'est l'ouvrante
			flag = 1;
		else if (flag == 1 && s[i] == '\'')// c'est la fermante
			flag = 0;
		// Si c'est une DQUOTE
		else if (flag == 0 && s[i] == '\"')// C'est l'ouvrante
			flag = 2;
		else if (flag == 2 && s[i] == '\"')// c'est la fermante
			flag = 0;
		i++;
	}
	//printf("%d = flag\n", flag);
	if (flag != 0)
		return (1);
	return (0);
}
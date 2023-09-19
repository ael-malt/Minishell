/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/19 17:13:00 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strrchr_(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c)
			return (1);
		i--;
	}
	return (0);
}

int	search_char(char *s) // chercher ';' et '\'
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strrchr_(&s[i], '\\') == 1 || ft_strrchr_(&s[i], ';') == 1)
			return (1);
		i++;
	}
	return (0);
}

int	search_quote(char *s) // chercher si les quote sont fermees (si elles sont par 2)
{
	int	i;
	int	simple_flag;
	int	double_flag;

	i = 0;
	simple_flag = 0;
	double_flag = 0;
	while (s[i])
	{
		printf("%c\n", s[i]);
		if (s[i] ==  '\'')
			simple_flag++;
		else if (s[i] =='\"')
			double_flag++;
		i++;
	}
	if (simple_flag % 2 == 0 && double_flag % 2 == 0)
		return (1);
	else
		return (0);
}
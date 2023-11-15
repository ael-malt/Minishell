/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_split_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:15:38 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/15 16:15:38 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (str[i])
	{
		if (check_charset(str[i], charset))
			i++;
		if (is_operator(str[i]) == 1)
		{
			word_count++;
			while (str[i] && !check_charset(str[i], charset) && \
				is_operator(str[i]) == 1)
				i++;
		}
		if (str[i])
		{
			word_count++;
			while (str[i] && !check_charset(str[i], charset))
				i++;
		}
	}
	return (word_count);
}

int	count_wlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !check_charset(str[i], charset))
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_split_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:30:38 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/14 17:06:03 by lazanett         ###   ########.fr       */
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

char	**ft_split_redir(char *str, char *charset)
{
	int		i;
	int		j;
	int		k;
	char	**strs;

	strs = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!strs)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_charset(str[i], charset))
			i++;
		if (str[i] && !check_charset(str[i], charset))
		{
			strs[j] = malloc(sizeof(char) * (count_wlen(&str[i], charset) + 1));
			k = 0;
			while (str[i] && !check_charset(str[i], charset))
				strs[j][k++] = str[i++];
			strs[j++][k] = 0;
		}
	}
	strs[j] = 0;
	return (strs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:38:56 by lazanett          #+#    #+#             */
/*   Updated: 2023/06/28 16:24:47 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}	

static char	**ft_free_split(char **split, int j)
{
	while (j)
	{
		free(split);
		j--;
	}
	free(split);
	return (split);
}

static char	**ft_retrecir(char **split, const char *s, char c, int index)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			if (!split [j - 1])
			{
				ft_free_split(split, j);
				return (split);
			}
			index = -1;
		}
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	split = ft_retrecir(split, s, c, -1);
	return (split);
}

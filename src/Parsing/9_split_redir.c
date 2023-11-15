/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_split_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:30:38 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/15 16:19:08 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_split_redir(char *str, char *charset, t_split *s)
{
	s->i = 0;
	s->j = 0;
	s->k = 0;
	s->strs = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!s->strs)
		return (0);
	while (str[s->i])
	{
		if (check_charset(str[s->i], charset))
			s->i++;
		if (str[s->i] && !check_charset(str[s->i], charset))
		{
			s->k = 0;
			if (is_operator(str[s->i]) == 1)
				operator_split_redir(str, charset, s);
			else
				word_split_redir(str, charset, s);
			s->strs[s->j++][s->k] = 0;
		}
	}
	return (s->strs[s->j] = 0, s->strs);
}

void	operator_split_redir(char *str, char *charset, t_split *s)
{
	int	count;
	int	temp;

	count = 0;
	temp = s->i;
	while (str[s->i] && is_operator(str[s->i]) == 1)
	{
		count++;
		s->i++;
	}
	s->i = temp;
	s->strs[s->j] = malloc(sizeof(char) * count + 1);
	while (str[s->i] && !check_charset(str[s->i], charset) \
		&& is_operator(str[s->i]) == 1)
		s->strs[s->j][s->k++] = str[s->i++];
}

void	word_split_redir(char *str, char *charset, t_split *s)
{
	s->strs[s->j] = malloc(sizeof(char) * \
		(count_wlen(&str[s->i], charset) + 1));
	while (str[s->i] && !check_charset(str[s->i], charset))
		s->strs[s->j][s->k++] = str[s->i++];
}

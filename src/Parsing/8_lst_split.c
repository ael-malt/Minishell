/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_lst_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:28:37 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/08 18:28:37 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**malloc_command_in_lst(char *s, char **split)
{
	int	i;
	int	size;

	i = 0;
	size = len_tab_command(s);
	split = malloc(sizeof(char *) * (len_tab_command(s) + 1));
	if (!split)
		return (NULL);
	while (i < size + 1)
	{
		split[i] = NULL;
		i++;
	}
	return (split);
}

char	*word_dup_in_split(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**assign_tab_command(char *s, t_lst *lst, t_split *sp)
{
	ft_memset(sp, 0, sizeof(t_split));
	sp->split = malloc_command_in_lst(lst->command, sp->split);
	while (s[sp->index])
	{
		if (s[sp->index] == '\'')
		{
			sp->flag = 1;
			get_limit_word_quote(s, sp);
		}
		else if (s[sp->index] == '\"')
		{
			sp->flag = 2;
			get_limit_word_quote(s, sp);
		}
		else if (s[sp->index] && s[sp->index] != '\"' && s[sp->index] != '\'' \
			&& s[sp->index] != ' ' && s[sp->index] != '\t')
			get_word_limit(s, sp);
		sp->flag = 0;
		sp->index++;
	}
	sp->split[sp->i] = NULL;
	return (sp->split);
}

void	get_word_limit(char *s, t_split *sp)
{
	sp->start = sp->index;
	while (s[sp->index] && s[sp->index] != ' ' && s[sp->index] != '\t')
		sp->index++;
	sp->end = sp->index;
	sp->index -= 1;
	sp->split[sp->i] = word_dup_in_split(s, sp->start, sp->end);
	sp->i += 1;
}

void	get_limit_word_quote(char *s, t_split *sp)
{
	sp->start = sp->index;
	sp->index++;
	if (sp->flag == 2)
		while (s[sp->index] && s[sp->index] != '\"')
			sp->index++;
	if (sp->flag == 1)
		while (s[sp->index] && s[sp->index] != '\'')
			sp->index++;
	if (s[sp->index])
	{
		sp->index++;
		while (s[sp->index] && (s[sp->index] != ' ' && s[sp->index] != '\t'))
			sp->index++;
	}
	sp->end = sp->index;
	sp->index -= 1;
	sp->split[sp->i] = word_dup_in_split(s, sp-> start, sp->end);
	sp->i += 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:03:59 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/13 16:40:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*search_expand_in_line(t_expand *ex, char *line)
{
	int	i;
	char *str1;
	char *str2;

	i = 0;
	str1 = NULL;
	str2 = NULL;
	while (line[i] || line == NULL)
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
			{
				if (line[i] == '$' && (line[i + 1] != ' ' && line[i + 1] != '\t' && line[i + 1] != '\0' && line[i + 1] != '$') /*&& quote_expand(i, line, last) == 0*/) // si cas precedent alors sup ici '$
					line = get_split_expand(str1, str2, ex, line, i);
				i++;
			}
		}
		if (line[i] == '$' && (line[i + 1] != ' ' && line[i + 1] != '\t' && line[i + 1] != '\0' && line[i + 1] != '$') /*&& quote_expand(i, line, last) == 0*/) // si cas precedent alors sup ici '$
			line = get_split_expand(str1, str2, ex, line, i);
		i++;
	}
	//free new command et expand ?
	return (line);
}

char *get_split_expand(char *str1, char *str2, t_expand *ex, char *line, int i)
{
	str1 = ft_strndup(line, 0, (i - 1));
	str2 = get_str2(ex, line, i);
	get_replace(ex);
	if (ex->replace != NULL)
		line = ft_strjoin_connect(ex, str1, str2);
	return (line);
}

char	*get_str2(t_expand *ex, char *line, int i)
{
	int		len;
	int		j;
	char *str;

	len = 0;
	j = 0;
	i++;
	len = len_expand(line, i);
	ex->expand = malloc(sizeof(char) * len + 1);
	len += i;
	str = ft_strndup(line, len, ft_strlen(line));
	while (i < len)
	{
		ex->expand[j] = line[i];
		j++;
		i++;
	}
	ex->expand[j] = '\0';
	return (str);
}

int len_expand(char *line, int i)
{
	int j = 0;
	
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '$' && line[i] != '\'' && line[i] != '\"')
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

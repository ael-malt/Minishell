/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:03:59 by lazanett          #+#    #+#             */
/*   Updated: 2023/12/04 18:28:57 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_lst(t_lst *lst, t_expand *ex)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		lst->command = search_expand_in_line(ex, lst->command, i);
		lst = lst->next;
	}
}

//check ligne 33 le i va trop loin avec le test: é'_euezyrç"ry"ury"éç_'ryfh"
char	*search_expand_in_line(t_expand *ex, char *line, int i)
{
	while (line && line[i])
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
				if (line[i] == '$' && (line[i + 1] != ' ' && line[i + 1] != \
					'\t' && line[i + 1] != '\0' && line[i + 1] != '$'))
					line = get_split_expand(ex, line, i);
				i++;
			}
		}
		if (line[i] == '$' && (line[i + 1] != ' ' && line[i + 1] != '\t' && \
			line[i + 1] != '\0' && line[i + 1] != '$'))
			line = get_split_expand(ex, line, i);
		i++;
	}
	return (line);
}

char	*get_split_expand(t_expand *ex, char *line, int i)
{
	ex->str1 = NULL;
	ex->str2 = NULL;
	ex->str1 = ft_strndup(line, 0, (i - 1));
	ex->str2 = get_str2(ex, line, i);
	get_replace(ex);
	if (ex->replace != NULL)
		line = ft_strjoin_connect(ex, ex->str1, ex->str2);
	free(ex->str1);
	free(ex->str2);
	return (line);
}

char	*get_str2(t_expand *ex, char *line, int i)
{
	int		len;
	int		j;
	char	*str;

	len = 0;
	j = 0;
	i++;
	len = len_expand(line, i);
	ex->expand = malloc(sizeof(char) * len + 1);
	if (!ex->expand)
		return (NULL);
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

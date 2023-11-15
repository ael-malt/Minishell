/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_expand_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:13:23 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/09 15:13:23 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_connect(t_expand *ex, char *start, char *end)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	get_len_strjoin_connect(ex, start, end);
	if (start)
	{
		while (start[i])
			ex->new_command[j++] = start[i++];
		i = 0;
	}
	if (ex->replace)
	{
		while (ex->replace[i])
			ex->new_command[j++] = ex->replace[i++];
		i = 0;
	}
	if (end)
		while (end[i])
			ex->new_command[j++] = end[i++];
	ex->new_command[j] = '\0';
	return (ex->new_command);
}

void	get_len_strjoin_connect(t_expand *ex, char *start, char *end)
{
	ex->k = 0;
	ex->l = 0;
	ex->m = 0;
	if (ex->replace == NULL && start == NULL && end == NULL)
		return ;
	if (ex->replace != NULL)
		ex->m = ft_strlen(ex->replace);
	else
		ex->replace = ft_strdup("");
	if (start != NULL)
		ex->k = ft_strlen(start);
	if (end != NULL)
		ex->l = ft_strlen(end);
	ex->new_command = malloc(sizeof(char) * (ex->k + ex->m + ex->l) + 1);
	if (!ex->new_command)
		return ;
}

char	*ft_strndup(char *s, int start, int end)
{
	int		i;
	char	*copy;

	i = 0;
	if (!s)
		return (NULL);
	if ((end - start) < 0)
		return (NULL);
	copy = malloc(sizeof (char) * ((end - start) + 2));
	if (!copy)
		return (NULL);
	while (s[start] && start <= end)
	{
		copy[i] = s[start];
		start++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	len_expand(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && \
		line[i] != '$' && line[i] != '\'' && line[i] != '\"')
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

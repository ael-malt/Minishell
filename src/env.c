/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:03:59 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/05 11:59:15 by lazanett         ###   ########.fr       */
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
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] != ' ' && line[i + 1] != '\t' && line[i + 1] != '\0' && line[i + 1] != '$')) // si cas precedent alors sup ici '$
		{
			str1 = ft_strndup(line, 0, (i - 1));
			//printf ("%s = str1 \n", str1);
			str2 = get_str2(ex, line, i);
			//printf ("%s = str2\n", str2);
			get_replace(ex);
			line = ft_strjoin_connect(ex, str1, str2);
			ft_free_expand(ex, str1, str2);
			// i = -1;
		}
		// printf("I :%d\n", i);
		i++;
	}
	return (line);
}

char	*get_str2(t_expand *ex, char *line, int i)
{
	int		len;
	int		j;
	char *str;

	len = 0;
	j = 0;
	i++;// aller apres $
	len = len_expand(line, i); // len de expand
	ex->expand = malloc(sizeof(char) * len);
	len += i;
	str = ft_strndup(line, len, ft_strlen(line));
	while (i < len)
	{
		ex->expand[j] = line[i];
		//printf("%c\n", ex->expand[j]);
		j++;
		i++;
	}
	return (str);
}

int len_expand(char *line, int i)
{
	int j = 0;
	
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '$')
	{
		i++;
		j++;
	}
	return (j);
}

char	*get_title(t_expand *ex, char *tab_str)
{
	int	j;

	j = 0;
	while (tab_str[j] != '=')
		j++;
	ex->title = malloc (sizeof (char) * j);
	if (!ex->title)
		return (NULL);
	j = 0;
	while (tab_str[j] != '=')
	{
		ex->title[j] = tab_str[j];
		j++;
	}
	//printf ("%s ===== title\n", ex->title);
	return (ex->title);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

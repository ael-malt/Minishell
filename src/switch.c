/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:20:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/12 15:23:54 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_title(t_expand *ex, char *tab_str)
{
	int	j;

	j = 0;
	while (tab_str[j] != '=')
		j++;
	ex->title = malloc (sizeof (char) * j + 1);
	if (!ex->title)
		return (NULL);
	j = 0;
	while (tab_str[j] != '=')
	{
		ex->title[j] = tab_str[j];
		j++;
	}
	ex->title[j]= '\0';
	return (ex->title);
}

void	get_replace(t_expand *ex)
{
	int	i;
	int	j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (ex->tab[i])
	{
		if (!ft_strcmp(get_title(ex, ex->tab[i]), ex->expand))
		{
			j += ft_strlen(ex->expand) + 1;
			while (ex->tab[i][j] != '\0')
			{
				count++;
				j++;
			}
			j -= count;
			ex->replace = malloc(sizeof (char) * count + 1);
			if (!ex->replace)
				return ;
			count = 0;
			while (ex->tab[i][j] != '\0')
			{
				ex->replace[count] = ex->tab[i][j];
				count++;
				j++;
			}
			ex->replace[count] = '\0';
			break ;
		}
		i++;
	}
	if (count == 0)
		ex->replace = NULL;
}

char	*ft_strjoin_connect(t_expand *ex, char *start, char *end)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (ex->replace == NULL)
		return (NULL);
	if (start != NULL)
		k = ft_strlen(start);
	if (end != NULL)
		l = ft_strlen(end);
	ex->new_command = malloc(sizeof(char) * (k + ft_strlen(ex->replace) + l) + 1); // + 1
	if (!ex->new_command)
		return (NULL);
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
	{
		while (end[i])
			ex->new_command[j++] = end[i++];
	}
	ex->new_command[j] = '\0';
	//printf("%s == new command\n", ex->new_command);
	return (ex->new_command);
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

void	ft_free_expand(t_expand *ex, char *str1, char *str2)
{
	if (ex->expand)
		free(ex->expand);
	// if (ex->replace)
	// 	free (ex->replace); //TODO FAUT FIX CE TRUC
	// if (ex->title)
	// 	free(ex->title);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	// if (ex->new_command)
	// 	free(ex->new_command);
}

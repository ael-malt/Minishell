/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:20:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/05 11:51:12 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		// printf("TAB = %s\n", ex->tab[i]);
		// printf("title = %s\n", ex->title);
		// printf("%s = expand\n", ex->expand);
		if (!ft_strcmp(get_title(ex, ex->tab[i]), ex->expand))
		{
			// printf("TAB = %s\n", ex->tab[i]);
			// printf("title = %s\n", ex->title);
			// printf("%s = expand\n", ex->expand);
			j += ft_strlen(ex->expand) + 1;
			while (ex->tab[i][j] != '\0')
			{
				count++;
				j++;
			}
			j -= count;
			ex->replace = malloc(sizeof (char) * count);
			if (!ex->replace)
				return ;
			count = 0;
			while (ex->tab[i][j] != '\0')
			{
				ex->replace[count] = ex->tab[i][j];
				count++;
				j++;
			}
			//printf("%s = replace\n", ex->replace);
		}
		i++;
	}
	if (!ex->replace)
	{
		printf("pas de correspondance\n");
		exit(0);
	}
	//printf("%s = replace\n", ex->replace);
}

char	*ft_strjoin_connect(t_expand *ex, char *start, char *end)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ex->new_command = malloc(sizeof(char) * (ft_strlen(start) + ft_strlen(ex->replace) + ft_strlen(end)) + 1); // + 1
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

void	ft_free_expand(t_expand *ex, char *str1, char *str2)
{
	if (ex->expand)
		free(ex->expand);
	if (ex->replace)
		free (ex->replace);
	if (ex->title)
		free(ex->title);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	// if (ex->new_command)
	// 	free(ex->new_command);
}
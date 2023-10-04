/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:20:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/04 15:03:52 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_str1(t_expand *ex, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '$')
	{
		count++;
		i++;
	}
	ex->str1 = malloc (sizeof (char) * (count + 1));
	if (!ex->str1)
		return ;
	i = 0;
	while (line[i] != '$')
	{
		ex->str1[i] = line[i];
		i++;
	}
	ex->str1[i] = '\0';
	printf("str1 == %s de len %d\n", ex->str1, count);
}

void	get_str2(t_expand *ex, char *line)
{
	int	i;
	int	j;
	int	start;
	int	count;

	i = 0;
	j = 0;
	start = 0;
	count = 0;
	while (line[i] != '$')
		i++;
	i++;
	while (line[i] != '\0' && line[i] != '$' && line[i] != '\t' && line[i] != ' ')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		printf("NO str2\n");
		return ;
	}
	//printf("%d\n", line[i]);
	start = i;
	while (line[i])
	{
		//printf("%c\n", line[i]);
		count++;
		i++;
	}
	ex->str2 = malloc (sizeof (char) * (count + 1));
	if (!ex->str2)
		return ;
	while (start < i) // == \0
	{
		ex->str2[j] = line[start];
		//printf("%c\n", ex->str2[j]);
		start++;
		j++;
	}
	ex->str2[j] = '\0';
	printf("str2 == %s de len %d\n", ex->str2, count);
}

char	*ft_strjoin_connect(t_expand *ex, char *start, char *end)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!start && !ex->replace && !end)
	{
		printf("rien a join\n");
		return (NULL);
	}
	ex->new_command = malloc(sizeof(char) * (ft_strlen(start) + ex->len_replace + ft_strlen(end))+ 1); // + 1
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
	printf("%s == new command\n", ex->new_command);
	return (ex->new_command);
}

void	ft_free_expand(t_expand *ex)
{
	if (ex->var)
		free(ex->var);
	if (ex->expand)
		free(ex->expand);
	if (ex->replace)
		free (ex->replace);
	if (ex->title)
		free(ex->title);
	if (ex->str1)
		free(ex->str1);
	if (ex->str2)
		free(ex->str2);
	ex->len_var = 0;
	ex->start_index = 0;
	ex->len_replace = 0;
	ex->len_title = 0;
}

void	line_expand(t_expand *ex, char *line, char **envp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			get_tab_env(ex, envp);
			search_expand_in_line(ex, line);
			get_replace(ex);
			get_str1(ex, line);
			get_str2(ex, line);
			ft_strjoin_connect(ex, ex->str1, ex->str2);
			//ft_free_expand(ex);
		}
		i++;
	}
}

// prendre tout avant $ dans commande de base
// rajouter replace
// et rajouter la suite de la commande apres variable env
// strjoin_connect de pipex ?
// voir si marche avec plusieurs varibale d'env
// guillemet a prendre en compte
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:03:59 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/04 15:01:33 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// REGARDER SI CA MARCHE POUR PLUSIEURS VARIABLE D'ENV
void	search_expand_in_line(t_expand *ex, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ex->expand = malloc(sizeof (char) * (len_expand(ex, line))); //+ 1
	if (!ex->expand)
		return ;
	while (line[i])
	{
		if (line[i] == '$')
		{
			ex->start_index = i;
			i++;
			while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '$' && j < len_expand(ex, line))
			{
				ex->expand[j] = line[i];
				j++;
				i++;
			}
			//ex->expand[j] = '\0'; // + 1?
			//printf("%s\n", ex->expand);
		}
		i++;
	}
}

int	len_expand(t_expand *ex, char *line)
{
	int	i;

	i = 0;
	ex->len_var = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			//printf("%c\n", line[i + 1]);
			//ex->len_var++;
			i++;
			if (line[i + 1] != '\0' || line[i + 1] != ' ' || line[i + 1] != '\t' || line[i + 1] != '$')
			{
				while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t' && line[i] != '$')
				{
					ex->len_var++;
					//printf("%c\n", line[i]);
					//printf("%d\n", ex->len_var);
					i++;
				}
			}
		}
		i++;
	}
	//printf("%d\n", ex->len_var);
	return (ex->len_var);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

int	len_var_in_tab(t_expand *ex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ex->len_replace = 0;
	while (ex->tab[i])
	{
		// printf("TAB================%s\n", ex->tab[i]);
		// printf("TITLE================%s\n", get_title(ex, ex->tab[i]));
		//printf("EX================%s\n", ex->expand);
		if (!ft_strcmp(get_title(ex, ex->tab[i]), ex->expand))
		{
			//printf("corres\n");
			j += ex->len_var + 1; // + = de la variable
			while (ex->tab[i][j] != '\0')
			{
				ex->len_replace++;
				j++;
			}
		}
		//printf("vcoycou\n");
		i++;
	}
	if (!ex->len_replace)
	{
		printf("pas variable comptible\n");
		exit(0);
	}
	return (ex->len_replace);
}

void	get_replace(t_expand * ex)
{
	int	i;
	int	index;
	int	j;
	char *temp;

	i = 0;
	index = 0;
	j = 0;
	temp = NULL;
	ex->replace = malloc (sizeof (char) * len_var_in_tab(ex)); // + 1 for \0 ?
	if (!ex->replace)
		return ;
	while (ex->tab[i])
	{
		if (!ft_strcmp(get_title(ex, ex->tab[i]), ex->expand))
		{
			j += ex->len_var + 1; // =
			while (ex->tab[i][j] != '\0')
			{
				ex->replace[index] = ex->tab[i][j];
				index++;
				j++;
			}
			printf("%s = replace\n", ex->replace);
		}
		i++;
	}
	
}

char	*get_title(t_expand *ex, char *tab_str)
{
	int	j;

	j = 0;
	ex->len_title = 0;
	while (tab_str[j] != '=')
	{
		ex->len_title++;
		j++;
	}
	ex->title = malloc (sizeof (char) * ex->len_title);
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
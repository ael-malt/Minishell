/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_switch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:20:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/09 15:17:43 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

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
	ex->title[j] = '\0';
	return (ex->title);
}

void	get_replace(t_expand *ex)
{
	ex->i = 0;
	ex->j = 0;
	ex->count = 0;
	ex->flag = 0;
	while (ex->tab[ex->i])
	{
		if (!ft_strcmp(get_title(ex, ex->tab[ex->i]), ex->expand))
		{
			assign_replace(ex);
			break ;
		}
		if (!ft_strcmp(ex->expand, "?"))
		{
			ex->replace = ft_itoa(g_exit_status);
			ex->count = 1;
		}
		ex->i++;
	}
	if (ex->count == 0)
		ex->replace = ft_strdup("");
}

void	assign_replace(t_expand *ex)
{
	ex->j += ft_strlen(ex->expand) + 1;
	while (ex->tab[ex->i][ex->j] != '\0')
	{
		ex->count++;
		ex->j++;
	}
	ex->j -= ex->count;
	ex->replace = malloc(sizeof (char) * ex->count + 1);
	if (!ex->replace)
		return ;
	ex->count = 0;
	while (ex->tab[ex->i][ex->j] != '\0')
	{
		ex->replace[ex->count] = ex->tab[ex->i][ex->j];
		ex->count++;
		ex->j++;
	}
	ex->flag = 1;
	ex->replace[ex->count] = '\0';
}

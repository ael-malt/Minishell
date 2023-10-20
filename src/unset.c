/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:54:21 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/20 18:33:19 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_var_in_tab(char *av, char **tab)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(av);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], av, len))
			return (i);
		i++;
	}
	return (0);
}

int	mini_unset(t_expand *ex, char **split_command)
{
	int	i;
	int	len;
	int	j;

	i = 1;
	if (!split_command)
		return (0);
	// ft_printf("%s\n", split_command[2]);
	while (split_command[i])
	{
		j = 0;
		len = ft_strlen(split_command[i]);
		if (len == 0)
			return (0);
		j = unset_var_in_tab(split_command[i], ex->tab);
		if (j)
		{
			ex->tab = new_tab(ex, j);
		}
		i++;
	}
	return (0);
}

char	**new_tab(t_expand *ex, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ex->new_tab = malloc(sizeof (char *) * len_tab(ex->tab));
	if (!ex->new_tab)
		return (0);
	while (ex->new_tab[i])
	{
		ex->new_tab[i] = NULL; // pas \0 car tt est mis a null
		i++;
	}
	i = 0;
	while (ex->tab[i])
	{
		if (!(i == index))
			ex->new_tab[j++] = ft_strdup(ex->tab[i]);
		i++;
	}
	ft_free(ex->tab);
	return (ex->new_tab);
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

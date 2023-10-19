/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:54:21 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/19 11:01:24 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	invalid_arg_unset(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-') // ou verif si s[0] == '-'
		{
			//printf("tiret dans arg de unset\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	cmp_unset(char **av, t_expand *ex)
{
	int	i;

	i = 0;
	if (!ft_strcmp(av[0],"unset"))
	{
		i = 1;
		while (av[i])
		{
			if (!invalid_arg_unset(av[i]))
				search_arg_unset(av[i], ex);
			i++;
		}
	}
}

void	search_arg_unset(char *av, t_expand *ex)
{
	int	i;
	int	len;

	i = 0;
	while (av[i])
		i++;
	len = i;
	if (len == 0)
		return ;
	i = 0;
	while (ex->tab[i])
	{
		if (ft_strncmp(get_title(ex, ex->tab[i]), av, len))
		{
			ex->tab = new_tab(ex, i);
			break ;
		}
		i++;
	}
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
		if (i == index)
		{
			free(ex->tab[i]);
			i++;
		}
		ex->new_tab[j] = ft_strdup(ex->tab[i]);
		i++;
		j++;
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
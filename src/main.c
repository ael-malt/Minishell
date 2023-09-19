/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/19 17:13:47 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	char	*line;
	if (ac == 1)
	{
		get_tab_env(envp);
		while (1)
		{
			line = readline("Minishell: ");
			if (line)
			{
				add_history(line);
				if (search_char(line) == 1)
					printf("Error : argument invalid \n");
			}
			//free line
		}
	}
	else
		printf("Error : nb argc invalid\n");
}

char	**get_tab_env(char **envp) // recup l'environnement
{
	int		i;
	char	**tab;

	i = 0;
	while (envp[i] != NULL)
		i++;
	tab = malloc (sizeof(char *) * i);
	if (!tab)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		tab[i] = ft_strdup(envp[i]);
		//printf("%s\n", tab[i]);
		i++;
	}
	return (tab);
}
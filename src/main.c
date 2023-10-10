/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 17:53:39 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_lst	*lst;
	t_lst *tmp;
	t_expand	ex;
	char	*line;
	char	*coucou;
	if (ac == 1)
	{
		get_tab_env(&ex, envp);
		while (1)
		{
			line = readline("Minishell: ");
			if (line)
			{
				add_history(line);
				coucou = search_expand_in_line(&ex, line);
				printf("%s\n", coucou);
				lst = create_node();
				lst->content = ft_strdup(coucou);
				//printf("%s\n", lst->content);
				split_command(lst);
				tmp = lst;
				while (tmp)
				{
					printf("command : %s\n ", tmp->command);
					tmp = tmp->next;
				}
			}
			// free line
		}
	}
	else
		printf("Error : nb argc invalid\n");
}

void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	ex->tab = malloc (sizeof(char *) * (size + 1));
	if (!ex->tab)
		return ;
	int i = 0;
	while (i < size + 1)
	{
		ex->tab[i] = NULL;
		i++;
	}
	i = 0;
	while (envp[i])
	{
		ex->tab[i] = ft_strdup(envp[i]);
		if (ex->tab[i] == 0)
		{
			free(ex->tab[i]);
			exit(1);
		}
		// printf("%s\n", ex->tab[i]);
		i++;
	}
	return;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 14:19:26 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_tree	*tree;
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
				tree = create_node();
				tree->content = ft_strdup(coucou);
				//printf("%s\n", tree->content);
				split_command(tree);
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

// char	**get_str(char *s) //commande a mettre dans un maillon; si nv commande aller vers la droite
// {
// 	int	i;
// 	int j;
// 	int k;
// 	char **tab;
// 	char *temp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	tab = malloc(sizeof(char *) * word_count(s));
// 	while (limiteur(s[i]) != 1 || s[i])
// 	{
// 		if (s[i] && s[i] == ' ')
// 			i++;
// 		if (limiteur(s[i]) != 1 && s[i] && s[i] != ' ')
// 		{
// 			temp = malloc(sizeof (char) * len_word_count(&s[i]));
// 			while (s[i] && s[i] != ' ')
// 			{
// 				temp[k] = s[i];
// 				i++;
// 				k++;
// 			}
// 			tab[j] = strdup(temp);
// 			printf("%s\n", tab[j]);
// 			//printf("%c\n", s[i]);
// 			j++;
// 			k = 0;
// 			free(temp);
// 			//temp = NULL;
// 		}
// 		if (limiteur(s[i]) == 1)
// 		{
// 			break;
// 			return (tab);
// 		}	
// 		if (s[i] == '\0')
// 			return (tab);
// 	}
// 	return (tab);
// }

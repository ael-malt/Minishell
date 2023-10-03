/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/03 17:08:30 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	(void) av;
// 	char	*line;
// 	if (ac == 1)
// 	{
// 		get_tab_env(envp);
		
// 		while (1)
// 		{
// 			line = readline("Minishell: ");
// 			if (line)
// 			{
// 				add_history(line);
// 				if (search_char(line) == 1 || search_quote(line) == 1)
// 					printf("Error : line invalid \n");
//				if (is_command_simple(line) == 0)
//					get_str(line);
//				else
//				{
// 					create_tree;
//					get_str(line);
//				}
// 				
// 			}
// 			//free line
// 		}
// 	}
// 	else
// 		printf("Error : nb argc invalid\n");
// }

int	main(int ac, char **av, char **envp)
{
	//t_tree	*tree;
	t_expand	ex;
	 (void) av;
	if (ac == 2)
	{
		get_tab_env(&ex, envp);
		//len_expand(&ex, av[1]);
		search_expand_in_line(&ex, av[1]);
		get_replace(&ex);
		// tree = create_node();
		// tree->content = ft_strdup(av[1]);
		// printf("%s\n", tree->content);
		// split_command(tree);
	}
}

void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	ex->tab = malloc (sizeof(char *) * i);
	if (!ex->tab)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		ex->tab[i] = ft_strdup(envp[i]);
		//printf("%s\n", ex->tab[i]);
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
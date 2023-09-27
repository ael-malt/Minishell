/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/27 17:26:48 by lazanett         ###   ########.fr       */
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

void	split_command(t_tree *tree) // simple ppinteur car renvoie une string
{
	len_split_command(tree);
	if (tree->len_command == tree->len_str1)// si le len = \0 quitte fonction
		return;
	if (tree->content[0] == '|')
		is_operator_split(tree);
	else
	{
		tree->str1 = ft_strndup(tree->content, 0, (tree->len_str1 - 1));
		tree->str2 = ft_strndup(tree->content, tree->len_str1, (tree->len_command - 1));
	}
	if (tree->str1)
	{
		tree->left = create_node();
		tree->left->content = tree->str1;
		printf("tree->left = %s\n", tree->left->content);
		tree->right = create_node();
		tree->right->content = tree->str2;
		printf("tree->right = %s\n", tree->right->content);
		split_command(tree->right);
	}
	//flag = 1;
	return;
}
// faire fonction pour detecter les operator

void	is_operator_split(t_tree *tree)
{
	int	i;

	i = 0; 
	tree->str1 = malloc(sizeof (char) * (len_operator(tree) + 1));
	while (tree->content[i] && tree->content[i] == '|')
	{
		tree->str1[i] = tree->content[i];
		i++;
	}
	tree->str1[i] = '\0';
	while (tree->content[i] == ' ')
		i++;
	tree->str2 = ft_strndup(tree->content, i, (tree->len_command - 1));
}

int	len_operator(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->content[i] && tree->content[i] == '|')
		i++;
	return (i);
}

void	len_split_command(t_tree *tree)
{
	int	i;

	i = 0;
	//printf("%s\n", tree->content);
	while (tree->content[i] != '\0')
		i++;
	tree->len_command = i;
	i = 0;
	while (tree->content[i] != '\0' && tree->content[i] != '|')
		i++;
	tree->len_str1 = i;
	//printf("len str1 = %d\n", tree->len_str1);
	//printf("len command = %d\n", tree->len_command);
}

int	main(int ac, char **av)
{
	t_tree	*tree;
	
	if (ac == 2)
	{
		tree = create_node();
		tree->content = av[1];
		split_command(tree);
	}
}

char	*ft_strndup(char *s, int start, int end)
{
	int i;
	char *copy;

	i = 0;
	if (!s)
		return (NULL);
	if ((end - start) < 0)
		return (NULL);
	copy = malloc(sizeof (char) * (end - start) + 1);
	if (!copy)
		return (NULL);
	while (s[start] && start <= end)
	{
		copy[i] = s[start];
		start++;
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_tree	*create_node()
{
	t_tree	*node;

	node = malloc(sizeof(t_tree)); 
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_tree));
	return (node);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:48 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/22 16:01:50 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*create(char *content) // creer un nv noeud
{
	t_tree	*node;

	node = malloc(sizeof(node)); // alloc de memoire
	if (!node)
		return (NULL);
	node->content = content; // le content
	node->left = NULL; // branche
	node->right = NULL; // branche
	return (node);
}

t_tree *insert(t_tree *tree, char *content)
{
	t_tree	*pres;
	t_tree	*top;

	if (!tree)
		return (create(content)); // commande
	while (tree) // balader dans l'arbre
	{
		pres = tree;
		if ()//droite en fonction des conditions
		else
	}
	//Puis creer l'element au bon endroit
	if (limiteur(line) == 1)
		create();
	else
		/*ajout la suite de la commande au maillon deja existant*/
	
}

int	limiteur(char c)
{
	if (c == '|' || c == '<' || c == '<<' ||
		c == '>' || c == ' ' || c == '>>')
		return (1);
	return (0);
}

char	get_str(char *s) //commande a mettre dans un maillon; si nv commande aller vers la droite
{
	int	i;
	char *str;

	i = 0;
	while (s[i])
	{
		if (limiteur(s[i]) == 1)
		{
			temp = i;
			i = 0;
			while (i < temp)
			{
				str[i] = s[i];
				i++;
			}
			i = temp;
		}
		i++;
	}
}


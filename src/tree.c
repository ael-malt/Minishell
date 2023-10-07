/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:48 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/07 16:09:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*create_node()
{
	t_tree	*node;

	node = malloc(sizeof(t_tree)); 
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_tree));
	return (node);
}

void	split_command(t_tree *tree)
{
	len_split_command(tree);
	if (tree->len_command == tree->len_str1 || res_is_operator(tree, tree->content) == 1)
		return;
	if (is_operator(tree->content[0]) == 1)
	{
		if (tree->content[0] == '|')
			is_operator_split(tree);
		if (tree->content[0] == '>' || tree->content[0] == '<')
		{
			tree->str1 = ft_strndup(tree->content, 0, len_redirection(tree, tree->content));
			tree->str2 = ft_strndup(tree->content, (len_redirection(tree, tree->content) + 1), (tree->len_command));
		}
	}
	else
	{
		tree->str1 = ft_strndup(tree->content, 0, (tree->len_str1 - 1));
		tree->str2 = ft_strndup(tree->content, tree->len_str1, (tree->len_command)); // - 1
	}
	if (tree->str1 && tree->str2)
		tree_branch(tree);
	return;
}

void	tree_branch(t_tree *tree)
{
	tree->left = create_node();
	tree->left->content = tree->str1;
	printf("tree->left = %s\n", tree->left->content);
	tree->right = create_node();
	tree->right->content = tree->str2;
	printf("tree->right = %s\n", tree->right->content);
	split_command(tree->right);
}

void	len_split_command(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->content[i] != '\0')
		i++;
	tree->len_command = i;
	i = 0;
	while (tree->content[i] != '\0' && is_operator(tree->content[i]) == 0)
		i++;
	tree->len_str1 = i;
}

char	*ft_strndup(char *s, int start, int end)
{
	int		i;
	char	*copy;

	i = 0;
	if (!s)
		return (NULL);
	if ((end - start) < 0)
		return (NULL);
	copy = malloc(sizeof (char) * ((end - start) + 2));
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

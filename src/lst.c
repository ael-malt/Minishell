/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:46:48 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 17:52:03 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lst	*create_node()
{
	t_lst	*node;

	node = malloc(sizeof(t_lst)); 
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_lst));
	return (node);
}

void	split_command(t_lst *lst)
{
	len_split_command(lst);
	
	if (is_operator(lst->content[0]) == 1)
	{
		if (lst->content[0] == '|') // content rest du pres
			is_operator_split(lst);
		if (lst->content[0] == '>' || lst->content[0] == '<')
		{
			lst->command = ft_strndup(lst->content, 0, len_redirection(lst, lst->content));
			lst->rest = ft_strndup(lst->content, (len_redirection(lst, lst->content) + 1), (lst->len_command_total));
		}
	}
	else
	{
		lst->command = ft_strndup(lst->content, 0, (lst->len_com - 1)); //
		lst->rest = ft_strndup(lst->content, lst->len_com, (lst->len_command_total)); // - 1
	}
	if (lst->len_com == lst->len_command_total)
		return;
	if (lst->rest && lst->command)
		tree_branch(lst);
	return;
}
//contwnt je garde cpmmande et j'emvoie au prochain rest
//rest = next content

void	tree_branch(t_lst *lst)
{
	lst->next = create_node();
	lst->next->prev = lst;
	lst->next->content = lst->rest;
	split_command(lst->next);
}

void	len_split_command(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst->content[i] != '\0')
		i++;
	lst->len_command_total = i;
	i = 0;
	while (lst->content[i] != '\0' && is_operator(lst->content[i]) == 0)
		i++;
	lst->len_com = i;
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

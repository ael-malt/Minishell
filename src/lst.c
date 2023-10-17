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
	int i;

	i = 0;
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
		lst->command = ft_strndup(lst->content, 0, (lst->len_com - 1));
		// printf("end = %d\n", (lst->len_com - 1));
		while (lst->command[i] != '\0')
		{
			printf("%d | %c\n",lst->command[i], lst->command[i]);
			i++;
		}
		printf("%d | %c\n",lst->command[i], lst->command[i]);
		lst->rest = ft_strndup(lst->content, lst->len_com, (lst->len_command_total)); // - 1
		// printf("end = %d\n", (lst->len_com - 1));
		// while (lst->rest[i] != '\0')
		// {
		// 	printf("%d | %c\n",lst->rest[i], lst->rest[i]);
		// 	i++;
		// }
		// printf("%d | %c\n",lst->rest[i], lst->rest[i]);
	}
	if (lst->len_com == lst->len_command_total)
		return;
	if (lst->rest && lst->command)
		tree_branch(lst);
	return;
}
//content je garde commande et j'envoie au prochain rest
//rest = next content

void	tree_branch(t_lst *lst)
{
	lst->next = create_node();
	lst->next->prev = lst; //mallon sur lequel on est
	lst->next->content = lst->rest; // prochain = rest
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

void	assign_token(t_lst *lst)
{
	if (!lst)
		return;
	while (lst)
	{
		if (lst->content[0] == '|')
			lst->token = 1;
		else if (lst->content[0] == '>' || lst->content[0] == '<')
			lst->token = 2;
		else
			lst->token = 0;
		//printf("lst = content === %s | lst->token %d \n", lst->content, lst->token);
		lst = lst->next;
	}
}
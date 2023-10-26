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

t_lst	*create_node(void)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst)); 
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_lst));
	// ft_memset(node, 0, sizeof(t_expand));
	return (node);
}

int	split_command(t_lst *lst, t_expand *ex)
{
	len_split_command(lst);
	//printf("%s\n", lst->content);
	if (is_operator(lst->content[0]) == 1)
	{
		if (lst->content[0] == '|' && len_operator(lst) != -1) // content rest du pres
			is_operator_split(lst);
		if (len_redirection(lst, lst->content) != -1 && (lst->content[0] == '>' || lst->content[0] == '<'))
		{
			lst->command = ft_strndup(lst->content, 0, len_redirection(lst, lst->content));
			lst->rest = ft_strndup(lst->content, (len_redirection(lst, lst->content) + 1), (lst->len_command_total));
		}
		else if (len_operator(lst) == -1 || len_redirection(lst, lst->content) == -1)
		{
			error_operator_message(lst->content);
			return (-1); 
		}
	}
	else
	{
		lst->command = ft_strndup(lst->content, 0, (lst->len_com - 1));
		lst->rest = ft_strndup(lst->content, lst->len_com, (lst->len_command_total)); // - 1
	}
	if (lst->len_com == lst->len_command_total)
		return (1);
	if (lst->rest && lst->command)
		if (tree_branch(lst, ex) == -1)
			return (-1);
	return (0);
}

int	tree_branch(t_lst *lst, t_expand *ex)
{
	lst->next = create_node();
	lst->next->prev = lst; //mallon sur lequel on est
	lst->next->content = lst->rest; // prochain = rest
	if (split_command(lst->next, ex) == -1)
		return (-1);
	return (0);
}

void	len_split_command(t_lst *lst)
{
	int	i;
	char quote = 0;

	i = 0;
	while (lst->content[i] != '\0')
		i++;
	lst->len_command_total = i;
	i = 0;
	while (lst->content[i] != '\0' && (is_operator(lst->content[i]) == 0 || (is_operator(lst->content[i]) == 1 && quote != 0))) {
		if (!quote && (lst->content[i] == '\'' || lst->content[i] == '"' ))
			quote = lst->content[i];
		else if (quote && lst->content[i] == quote)
			quote = 0;
		i++;
	}
	lst->len_com = i;
}

void	assign_token(t_lst *lst)
{
	if (!lst)
		return;
	while (lst)
	{
		if (lst->command[0] == '|')
			lst->token = 1;
		else if (lst->command[0] == '>' || lst->command[0] == '<')
			lst->token = 2;
		else
			lst->token = 0;
		//printf("command %s, token = %d\n", lst->command, lst->token);
		lst = lst->next;
	}
}

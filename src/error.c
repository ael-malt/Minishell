/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/23 03:13:21 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

void	*mini_perror(int err_type, char *param, int err)
{
	g_exit_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote\n", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed\n", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed\n", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe\n", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device\n", 2);
	else if (err_type == IS_DIR)
		ft_putstr_fd("minishell: Is a directory: ", 2);
	else if (err_type == NOT_DIR)
		ft_putstr_fd("minishell: Not a directory: ", 2);
	ft_putendl_fd(param, 2);
	return (NULL);
}

int		mini_export_error(char *arg)
{
	char	*value;
	int		i;
	int		j;
	
	i = ft_strchr_i(arg, '=');
	if (i == -1)
		i = ft_strlen(arg);
	value = malloc(sizeof(char) * (i + 1));
	if (!value)
		return(1);
	j = 0;
	while (j <= i)
	{
		value[j] = arg[j];
		j++;
	}
	value[j] = '\0';
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("' not an identifier\n", 2);
	return (1);
}

void	*mini_perror2(int err_type, char param, int err)
{
	//printf("sgsd");
	g_exit_status = err;
	//printf("%d\n", g_exit_status);
	if (err_type == OPERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write (2, &param, 1);
		ft_putendl_fd("'", 2);
	}
	return (NULL);
}

// void	free_lst(t_lst *lst)
// {
// 	if (!lst)
// 		return ;
// 	while (lst->prev)
// 		lst = lst->prev;
// 	while (lst->next)
// 	{
// 		printf("FREE `%s'= lst command \n", lst->command);
// 		printf("FREE = lst content = %s\n", lst->content);
// 		free(lst->content);
// 		free(lst->command);
// 		if (lst->token == 1)
// 			ft_free(lst->split_command);
// 		lst = lst->next;
// 		free(lst->prev);
// 	}
// 	lst = NULL;
// }

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}


void	ft_free_expand(t_expand *ex)
{
	if (ex->expand)
		free(ex->expand);
	if (ex->replace)
		free (ex->replace);
	if (ex->title)
		free(ex->title);
	if (ex->new_command)
		free(ex->new_command);
}
void	clean_return(t_lst *lst, t_expand *ex)
{
	(void) ex;
	// ft_free_expand(ex); // pas ca car pas encore expand
	free_lst(lst);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:06:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/12/04 18:15:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

void	*mini_perror(int err_type, char *param, int err)
{
	g_exit_status = err;
	if (err_type == QUOTE)
		ft_putstr_fd("minishell: error while looking for matching quote", 2);
	else if (err_type == NDIR)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
	else if (err_type == NPERM)
		ft_putstr_fd("minishell: permission denied: ", 2);
	else if (err_type == NCMD)
		ft_putstr_fd("minishell: command not found: ", 2);
	else if (err_type == DUPERR)
		ft_putstr_fd("minishell: dup2 failed", 2);
	else if (err_type == FORKERR)
		ft_putstr_fd("minishell: fork failed", 2);
	else if (err_type == PIPERR)
		ft_putstr_fd("minishell: error creating pipe", 2);
	else if (err_type == MEM)
		ft_putstr_fd("minishell: no memory left on device", 2);
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

void	*mini_heardoc_error(int err_type, char *param, int err)
{
	//printf("sgsd");
	g_exit_status = err;
	//printf("%d\n", g_exit_status);
	if (err_type == OPERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write (2, &param, ft_strlen(param));
		ft_putendl_fd("'", 2);
	}
	if (err_type == NONAME)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2);
	if (err_type == SYNTAX)
		ft_putendl_fd("minishell: expected a command", 2);
	return (NULL);
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
void	*mini_perror_exec(int err_type, char **split_command)
{
	//g_exit_status = err;
	//printf("%d\n", g_exit_status);
	//printf("coucou\n");
	if (err_type == NOTCMD)
	{
		//printf("split_command = %s\n", split_command[0]);
		write (2, split_command[0], ft_strlen(split_command[0])); // regarder si strlen peut peter
		ft_putendl_fd(": command not found", 2);
		// ft_printf("%s: command not found\n", split_command[0]);
		
	}
	else if (err_type == NOT_DIR)
	{
		int i = 0;
		ft_putstr_fd("minishell: ", 2);
		while (split_command[i])
		{
			ft_putstr_fd(split_command[i], 2);
			i++;
		}
		ft_putendl_fd(": Not a directory", 2);
		//g_exit_status = err;
		//exit(EXIT_FAILURE);
	}
	return (NULL);
}
void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	// while (lst && lst->prev)
	// 	lst = lst->prev;
	ft_printf("lst->content: %s\n", lst->content);
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->next)
			tmp = lst->next;
		else
			tmp = NULL;
		// if (lst->content)
		// 	free(lst->content);
		// free(lst->command);
		// free(lst->split_command);
		// if (lst && lst->rest)
		// 	free(lst->rest);
		// free(lst);
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


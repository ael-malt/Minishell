/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/27 14:12:49 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h" 

extern int	g_exit_status;

/* 
TO-DO
	Builtins:
	- Si le builtin est avec une redirection gerer correctement si child ou pas

DONE
	Builtins:
	- Si le builtin est dans un pipe ne pas le faire dans un fork sinon le faire directement
	- cd
	- exit
	- echo
	- pwd
	- export
	- env
	- unset
	
	- exit avec plus d'un arg = erreur
	
	Autres:
	- initialiser toutes les variables de la lst en NULL des le debut
	- Faire un jolie message minishell;
	- executables normaux
	- fix signals
	- mettre des couleurs dans l'affichage
	- recevoir SIG_QUIT quand u prompt est ouvert (ex cat ou wc) 
*/
int	builtin(t_lst *lst, t_expand *ex)
{
	if (!ft_strcmp(lst->split_command[0], "pwd"))
		g_exit_status = mini_pwd();
	else if(!ft_strcmp(lst->split_command[0], "env"))
	{
		ft_putmatrix_fd(ex->tab, 1, 1);
		g_exit_status = 0;
	}
	else if(!ft_strcmp(lst->split_command[0], "export"))
		g_exit_status = mini_export(ex, lst->split_command);
	else if(!ft_strcmp(lst->split_command[0], "unset"))
		g_exit_status = mini_unset(ex, lst->split_command);
	else if(!ft_strcmp(lst->split_command[0], "echo"))
		g_exit_status = mini_echo(lst);
	else if(!ft_strcmp(lst->split_command[0], "exit"))
		g_exit_status = mini_exit(lst->split_command);
	else if(!ft_strcmp(lst->split_command[0], "cd"))
		g_exit_status = mini_cd(ex, lst->split_command);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (g_exit_status);
}

int	is_builtin(t_lst *lst)
{
	if (!lst->split_command)
		return (0);
	if (!ft_strcmp(lst->split_command[0], "pwd"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "env"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "export"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "unset"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "echo"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "exit"))
		return (1);
	else if(!ft_strcmp(lst->split_command[0], "cd"))
		return (1);
	return (0);
}


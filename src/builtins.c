/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/23 04:13:59 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h" 

extern int	g_exit_status;

/* 
TO-DO
	Builtins:
	- fix signals
	- verif cd (minishell: export: `�j�E�' not an identifier)
	- mettre des couleurs dans l'affichage
	- initialiser toutes les variables de la lst en NULL des le debut

DONE
	Builtins:
	- cd
	- exit
	- echo
	- pwd
	- export
	- env
	- unset
	
	Autres:
	- Faire un jolie message minishell;
	- executables normaux
*/
int	builtin(t_lst *lst, t_expand *ex)
{
	if (!ft_strncmp(lst->split_command[0], "pwd", 3))
		g_exit_status = mini_pwd();
	else if(!ft_strncmp(lst->split_command[0], "env", 4))
	{
		ft_putmatrix_fd(ex->tab, 1, 1);
		g_exit_status = 0;
	}
	else if(!ft_strncmp(lst->split_command[0], "export", 6))
		g_exit_status = mini_export(ex, lst->split_command);
	else if(!ft_strncmp(lst->split_command[0], "unset", 5))
		g_exit_status = mini_unset(ex, lst->split_command);
	else if(!ft_strncmp(lst->split_command[0], "echo", 4))
		g_exit_status = mini_echo(lst);
	else if(!ft_strncmp(lst->split_command[0], "exit", 4))
		g_exit_status = mini_exit(lst->split_command);
	else if(!ft_strncmp(lst->split_command[0], "cd", 2))
		g_exit_status = mini_cd(ex, lst->split_command);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (g_exit_status);
}

int	mini_echo(t_lst *lst)
{
	int	i;
	int	n;
	int	j;
	
	i = 1;
	n = 0;
	while (lst->split_command[i] && !ft_strncmp(lst->split_command[i], "-n", 2))
	{
		j = 1;
		while(lst->split_command[i][++j] == 'n');
		if (lst->split_command[i][j - 1] && lst->split_command[i][j] == '\0')
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	while (lst->split_command && lst->split_command[i])
	{
		ft_printf("%s",lst->split_command[i]);
		if (lst->split_command[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
	return (0);
}

int mini_exit(char **split_command)
{
	int n;
	int i;
	int is_num;

	n = 0;
	i = 1;
	is_num = 1;
	ft_printf("exit\n");
	if (split_command[1])
	{
		while (split_command[1][i])
		{
			if (!ft_isdigit(split_command[1][i]) || split_command[1][0] != '-')
				is_num = 0;
			i++;
		}
		if (is_num)
		{
			n = ft_atoi(split_command[1]);
			if (n >= 0 && n <= 255)
				g_exit_status = n;
			else
				g_exit_status = n % 256;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ", 2);
			ft_putendl_fd(split_command[1], 2);
			g_exit_status = 2;
		}
	}
	exit(g_exit_status);
}

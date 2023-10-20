/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/20 18:40:43 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h" 

extern int	g_exit_status;

/* 
TO-DO
	Builtins:
	- cd
	- fix signals
	- mettre des couleurs dans l'affichage
	- initialiser toutes les variables de la lst en NULL des le debut

DONE
	Builtins:
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
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	return (g_exit_status);
}

int	mini_pwd(void)
{
	char	*buf;

	
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

static int	export_var_in_tab(char *cmd, char **tab)
{
	int i;
	int	pos;

	i = 0;
	pos = ft_strchr_i(cmd, '=');
	if (pos == -1)
		return (-1);
	while (tab[i])
	{
		if (!ft_strncmp(tab[i], cmd, pos + 1))
			return (i);
		i++;
	}
	return (0);
}

int mini_export_verif(char *str)
{
	int	i;
	int	equal_present;
	
	i = 1;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return(0);
	equal_present = 0;
	while (str && str[i])
	{
		if(!(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '='))
			return (0);
		if (str[i] == '=')
			equal_present = 1;
		i++;
	}
	if (!equal_present)
		return(2);
	return (1);
}

int mini_export(t_expand *ex, char **split_command)
{
	int		i;
	int		pos;
	int		status_error;

	status_error = 0;
	i = 1;
	while (split_command[i])
	{
		if (mini_export_verif(split_command[i]) == 1)
		{
			pos = export_var_in_tab(split_command[i], ex->tab);
			if (pos)
			{
				free(ex->tab[pos]);
				ex->tab[pos] = ft_strdup(split_command[i]);
			}
			else if (!pos)
				ex->tab = ft_extend_matrix(ex->tab, split_command[i]);
		}
		else if(mini_export_verif(split_command[i]) == 0)
			status_error = mini_export_error(split_command[i]);
		else if (mini_export_verif(split_command[i]) == 2)
			status_error = 0;
		i++;
	}
	return (status_error);
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
			ft_printf("minishell: exit: %s: numeric argument required\n", split_command[1]);
			g_exit_status = 2;
		}
	}
	exit(g_exit_status);
}

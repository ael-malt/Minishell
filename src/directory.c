/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/23 16:42:58 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

int	mini_cd_error(char **split_command)
{
	DIR	*dir;
	int	exit_status;

	dir = NULL;
	exit_status = 0;
	if (split_command[1])
		dir = opendir(split_command[1]);
	if (split_command[1] && dir && access(split_command[1], F_OK) != -1)
		chdir(split_command[1]);
	else if(split_command[1] && access(split_command[1], F_OK) == -1)
	{
		mini_perror(NDIR, split_command[1], 1);
		exit_status = 1;
	}
	else if(split_command[1] && access(split_command[1], R_OK) == -1)
	{
		mini_perror(NPERM, split_command[1], 1);
		exit_status = 1;
	}
	else if(split_command[1])
	{
		mini_perror(NOT_DIR, split_command[1], 1);
		exit_status = 1;
	}
	if (split_command[1] && dir)
		closedir(dir);
	return (exit_status);
}

// protect old pwd, when current dir is delete, 
//
int	mini_cd(t_expand *ex, char **split_command)
{
	char	**pwd;
	int		exit_status;
	char *tmp;
	int		i;

	pwd = malloc(sizeof(char *) * 4);
	if (!pwd)
		return (1);
	exit_status = 0;
	i = export_var_in_tab("HOME=", ex->tab);
	if (i == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exit_status = 1;
	}
	pwd[0] = ft_strdup("export");
	tmp = getcwd(NULL, 0);
	pwd[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	// ft_printf("%s\n", pwd[1]);
	// mini_export(ex, pwd);
	if (ft_matrixlen(split_command) == 1 && i != 0)
		chdir(&ex->tab[i][5]);
	else if (ft_matrixlen(split_command) > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		exit_status = 1;
	}
	else
		exit_status = mini_cd_error(split_command);
	// free(pwd[1]);
	tmp = getcwd(NULL, 0);
	pwd[2] = ft_strjoin("PWD=", tmp);
	// ft_printf("%s\n", pwd[1]);
	// mini_export(ex, pwd);
	free(pwd[0]);
	free(pwd[1]);
	free(pwd[2]);
	free(tmp);
	free(pwd);
	return (exit_status);
}

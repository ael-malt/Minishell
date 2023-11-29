/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:03:47 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/29 17:18:57 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	mini_cd_error(char *join_cd, int *exit_status)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(join_cd);
	if (join_cd && dir && access(join_cd, F_OK) != -1)
		chdir(join_cd);
	else if (join_cd && access(join_cd, F_OK) == -1)
	{
		mini_perror(NDIR, join_cd, 1);
		*exit_status = 1;
	}
	else if (join_cd && access(join_cd, R_OK) == -1)
	{
		mini_perror(NPERM, join_cd, 1);
		*exit_status = 1;
	}
	else if (join_cd)
	{
		mini_perror(NOT_DIR, join_cd, 1);
		*exit_status = 1;
	}
	if (join_cd && dir)
		closedir(dir);
}

static void	mini_export_pwd(char *tmp, t_expand *ex)
{
	char	**pwd;

	pwd = malloc(sizeof(char *) * 4);
	if (!pwd)
		return ;
	pwd[0] = ft_strdup("export");
	pwd[1] = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	pwd[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	// ft_printf("pwd: %s\n", pwd[2]);
	pwd[3] = NULL;
	mini_export(ex, pwd);
	free(pwd[0]);
	free(pwd[1]);
	free(pwd[2]);
	free(pwd);
}

static char	*check_case(char *jcd, t_expand *ex)
{
	if (!strcmp(jcd, ".."))
	{
		free(jcd);
		jcd = ft_strdup("../");
	}
	if (!strcmp(jcd, "-"))
	{
		// ft_printf("nb: %d\n", export_var_in_tab("OLDPWD=", ex->tab));
		if (export_var_in_tab("OLDPWD=", ex->tab) != -1)
		{
			free(jcd);
			jcd = ft_strdup(&ex->tab[export_var_in_tab("OLDPWD=", ex->tab)][7]);
		}
		else 
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	}
	return (jcd);
}

static char *join_split_command(char **split_command, t_expand *ex)
{
	char	*join_str;
	int	i;

	join_str = ft_strdup(split_command[0]);
	if (split_command[1])
		join_str = ft_strjoin(join_str, " ");
	i = 1;
	while (split_command && split_command[i])
	{
		join_str = ft_strjoin(join_str, split_command[i]);
		if (split_command[i + 1])
			join_str = ft_strjoin(join_str, " ");
		i++;
	}
	join_str = check_case(join_str, ex);
	return (join_str);
}

int	mini_cd(t_expand *ex, char **split_command)
{
	int		exit_status;
	char	*cwd;
	char	*join_cd;
	int		i;

	cwd = NULL;
	join_cd = NULL;
	exit_status = 0;
	i = export_var_in_tab("HOME=", ex->tab);
	if (i == -1)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	cwd = getcwd(cwd, 0);
	ft_printf("cwd: %s\n", cwd);
	if (cwd)
	{
		if (ft_matrixlen(split_command) == 1 && i != 0)
			chdir(&ex->tab[i][5]);
		else
		{
			join_cd = join_split_command(split_command + 1, ex);
			if (ft_strcmp(join_cd, "-"))
				mini_cd_error(join_cd, &exit_status);
		}
	}
	return (mini_export_pwd(cwd, ex), free(join_cd), exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/12 15:17:22 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h" 

extern int	g_exit_status;

int	builtin(char *cmd, t_expand	ex)
{
	while (cmd[0] == ' ' || (cmd[0] >= '\a' && cmd[0] <= '\r'))
		cmd++;
	if (!ft_strncmp(cmd, "pwd", 3))
		g_exit_status = mini_pwd();
	else if(!ft_strncmp(cmd, "env", 4))
	{
		ft_putmatrix_fd(ex.tab, 1, 1);
		g_exit_status = 0;
	}
	else if(!ft_strncmp(cmd, "export", 6))
		mini_export(ex, cmd);
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

int ft_getkeyvalue(char *cmd, char *key, char *value)
{
	int		i;
	int		j;
	int		k;

	i = 5;
	j = 5;
	while(cmd[i] != '=')
		i++;
	if(!cmd[i])
		return (0);
	key = malloc(sizeof(char *) * (i - 5));
	if (!key)
		return(0);
	k = 0;
	while (j <= i)
	{
		key[k] = cmd[j];
		j++;
		k++;
	}
	k = 0;
	value = malloc(sizeof(char *) * (strlen(cmd) - 6));
	if (!cmd)
		return(0);
	while (cmd[i])
	{
		value[k] = cmd[i];
		i++;
		k++;
	}
	return (1);
}


int mini_export(t_expand ex, char *cmd)
{
	// int		ij[2];
	// int		pos;
	// char	**argv;
	(void) ex;
	char	*key;
	char	*value;
	
	key = NULL;
	value = NULL;
	ft_getkeyvalue(cmd, key, value);
	ft_printf("key: %s\nvalue: %s\n", key, value);
	// if (ft_matrixlen(argv) >= 2)
	// {
	// 	ij[0] = 1;
	// 	while (argv[ij[0]])
	// 	{
	// 		pos = var_in_envp(argv[ij[0]], prompt->envp, ij);
	// 		if (pos == 1)
	// 		{
	// 			free(prompt->envp[ij[1]]);
	// 			prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
	// 		}
	// 		else if (!pos)
	// 			prompt->envp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
	// 		ij[0]++;
	// 	}
	// }
	return (0);
}
int	mini_echo(t_list *cmd)
{
	int		newline;
	int		i[2];
	char	**argv;
	t_mini	*node;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	node = cmd->content;
	argv = node->full_cmd;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:24:48 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/19 11:01:09 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h" 

extern int	g_exit_status;

int	builtin(char *cmd, t_expand	*ex)
{
	while (cmd[0] == ' ' || (cmd[0] >= '\a' && cmd[0] <= '\r'))
		cmd++;
	if (!ft_strncmp(cmd, "pwd", 3))
		g_exit_status = mini_pwd();
	else if(!ft_strncmp(cmd, "env", 4))
	{
		ft_putmatrix_fd(ex->tab, 1, 1);
		g_exit_status = 0;
	}
	else if(!ft_strncmp(cmd, "export", 6))
		g_exit_status = mini_export(ex, cmd);
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

static int	var_in_envp(char *cmd, char **envp, int i)
{
	int	pos;

	i = 0;
	pos = ft_strchr_i(cmd, '=');
	if (pos == -1)
		return (-1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], cmd, pos + 1))
			return (1);
		i++;
	}
	return (0);
}

int mini_export(t_expand *ex, char *cmd)
{
	int		i;
	int		pos;
	
	i = 0;
	while (i < 6)
	{
		cmd++;
		i++;
	}
	while ((cmd[0] >= '\a' && cmd[0] <= '\r') || cmd[0] == ' ')
		cmd++;
	i = 0;
	pos = var_in_envp(cmd, ex->tab, i);
	if (pos == 1)
	{
		free(ex->tab[i]);
		ex->tab[i] = ft_strdup(cmd);
	}
	else if (!pos)
	ex->tab = ft_extend_matrix(ex->tab, cmd);
	i++;
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

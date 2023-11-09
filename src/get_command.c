/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:49:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/13 10:49:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

void	solo_exe(t_lst *lst, t_expand *ex)
{
	int	pid;
	int	status;
	int fd[2];
	(void) fd;

	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (ft_strchr(lst->split_command[0], '/') != NULL && !is_builtin(lst))
			exc_absolut_way(lst);
		else if (!is_builtin(lst))
			excecuting(lst, ex->tab);
		else if (is_builtin(lst))
			exit(0);
	}
	else
	{
		if (is_builtin(lst))
			builtin(lst, ex);
		//waitpid(pid, NULL, 0);
		//if (WEXITSTATUS(pid) > 0
		// close(fd[0]);
		// close(fd[1]);
		waitpid(pid, &status, 0);
		// Utilisez la macro WEXITSTATUS pour obtenir la valeur de retour
		//if (WIFEXITED(status))
		//printf("%d\n", status);
		g_exit_status = status / 256;
		//printf("%d\n", g_exit_status);

	}
	//printf("var globale = %d\n", g_exit_status);
}

void	excecuting(t_lst *lst, char **tab)
{
	int		i;
	int		index;
	char	**path;
	char	*chemin;

	i = 0;
	index = unset_var_in_tab("PATH", tab);
	path = ft_split(tab[index] + 5, ':');
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", lst->split_command[0]); // change valeur var global
		//perror("No PATH"); // modif plus tard
	}
	while (path[i++])
	{
		chemin = ft_strjoin_connect2(path[i], lst->split_command[0], '/');
		// int i = 0;
		// while (lst->split_command[i])
		// {
		// 	printf("%s\n", lst->split_command[i]);
		// 	i++;
		// }
		if (access(chemin, F_OK) == 0)
		{
			if (execve(chemin, lst->split_command, NULL) == -1)
			{
				mini_perror_exec(NOTCMD, lst->split_command);
				exit(127);
			}
		}
		free(chemin);
	}
	//ft_free(split_command);
	//ft_free(path);
	mini_perror_exec(NOTCMD, lst->split_command);
	exit(127);// 127 var global
	//perror("command not found");
}

void	exc_absolut_way(t_lst *lst)
{
	if (access(lst->split_command[0], F_OK) == 0)
	{
		if (execve(lst->split_command[0], lst->split_command, NULL) == -1)
		{
			//ft_free(lst->split_command);
			// printf("%s", lst->split_command[0]);
			// perror("");
			mini_perror_exec(NOT_DIR, lst->split_command); // verif chemin ab
			exit(127);
		}
	}
	else
	{
	// 	ft_free(lst->split_command);
		//printf("%s", lst->split_command[0]);
		//perror("");
		mini_perror_exec(NOT_DIR, lst->split_command); // verif pour chemin absolu
		exit(126);
	}
	// ft_free(lst->split_command);
}

char	*ft_strjoin_connect2(char const *s1, char const *s2, char connector)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 2));
		if (!str)
			return (NULL);
		while (s1[i])
			str[j++] = s1[i++];
		str[j++] = connector;
		i = 0;
		while (s2[i])
			str[j++] = s2[i++];
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}

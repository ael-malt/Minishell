/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:56:53 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/29 17:27:23 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

void	execute(t_lst *lst, t_expand *ex)
{
	// fprintf(stderr, "execute %s %d\n", lst->command, lst_count_redir(lst));
	if (is_builtin(lst) && (lst_count_pipe(lst) || lst_count_redir(lst)))
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (is_builtin(lst) && !lst->prev && !lst->next)
		exit(0);
	else if (!is_builtin(lst) &&ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else if (!is_builtin(lst))
		excecuting(lst, ex->tab);
}

void	excecuting(t_lst *lst, char **tab)
{
	int		i;
	int		index;
	char	**path;
	char	*chemin;

	i = 0;
	index = unset_vintab("PATH", tab);
	path = ft_split(tab[index] + 5, ':');
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", lst->split_command[0]); // change valeur var global
		//perror("No PATH"); // modif plus tard
	}
	while (path[i++])
	{
		if (lst->split_command)
			chemin = ft_strjoin_connect2(path[i], lst->split_command[0], '/');
		// int i = 0;
		// while (lst->split_command[i])
		// {
		// 	printf("%s\n", lst->split_command[i]);
		// 	i++;
		// }
		if (chemin)
		{
			if (chemin && access(chemin, F_OK) == 0)
			{
				// ft_printf("chemin: %s\n", chemin);
				if (execve(chemin, lst->split_command, tab) == -1)
				{
					mini_perror_exec(NOTCMD, lst->split_command); // cette erreur
					exit(127);
				}
			}
			free(chemin);
		}
		else (exit(g_exit_status));
	}
	//ft_free(split_command);
	//ft_free(path);
	mini_perror_exec(NOTCMD, lst->split_command);
	exit(127);// 127 var global
	//perror("command not found");
	
}

void	exc_absolut_way(t_lst *lst, t_expand *ex)
{
	if (access(lst->split_command[0], F_OK) == 0)
	{
		if (execve(lst->split_command[0], lst->split_command, ex->tab) == -1)
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

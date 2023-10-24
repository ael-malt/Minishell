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

int	is_solo_ex(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst->next)
	{
		if (lst->token == 1 || lst->token == 2)
			count++;
		lst = lst->next;
	}
	return (count);
}

void	solo_exe(t_lst *lst, t_expand *ex)
{
	int pid;

	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
	{
		if (is_builtin(lst) == 1)
			builtin(lst, ex);
		else if (ft_strchr(lst->split_command[0], '/') != NULL)
			exc_absolut_way(lst);
		else
			excecuting(lst->split_command, ex->tab);
	}
	else
		waitpid(pid, NULL, 0);
}

void	excecuting(char **split_command, char **tab)
{
	int		i;
	int		index;
	char	**path;
	char	*chemin;


	i = 0;
	index = unset_var_in_tab("PATH", tab);
	path = ft_split(tab[index] + 5, ':');
	if (path == NULL)
		perror("No PATH");
	//for (int i = 0; split_command[i]; i++)
	//	printf("%s\n", split_command[i]);
	while (path[i++])
	{
		chemin = ft_strjoin_connect2(path[i], split_command[0], '/');
		//printf("chemin | %s\n", chemin);
		if (access(chemin, F_OK) == 0)
		{
			if (execve(chemin, split_command, NULL) == -1)
				perror("command not found ex");
		}
		free(chemin);
	}
	//ft_free(split_command);
	//ft_free(path);
	perror("command not found acc");
}

int	is_builtin(t_lst *lst)
{
	if (!lst->split_command)
		return (0);
	if (!ft_strncmp(lst->split_command[0], "pwd", 3))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "env", 4))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "export", 6))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "unset", 5))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "echo", 4))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "exit", 4))
		return (1);
	else if(!ft_strncmp(lst->split_command[0], "cd", 2))
		return (1);
	return (0);
}

char	**ft_split_path(char **envp)
{
	int		i;
	char	**path_split;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			path_split = ft_split(envp[i] + 5, ':');
			return (path_split);
		}
		i++;
	}
	return (NULL);
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

void	exc_absolut_way(t_lst *lst)
{
	if (access(lst->split_command[0], F_OK) == 0)
	{
		if (execve(lst->split_command[0], lst->split_command, NULL) == -1)
		{
			//ft_free(lst->split_command);
			//ft_perror("command not found");
			printf("no excev\n");
		}
	}
	else
		printf("no acces\n");
	// {
	// 	ft_free(lst->split_command);
	// 	ft_perror("command not found");
	// }
	// ft_free(lst->split_command);
}
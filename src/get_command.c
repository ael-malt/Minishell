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

// gerer les erreurs de command pas existante
// etendre aux builins // gerer les erreurs
// redirection

extern int	g_exit_status;

void	solo_exe(t_lst *lst, t_expand *ex)
{
	int	pid;
	int	status;
	int fd[2];
	(void) fd;
	int	flag;

	flag = 0;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (is_builtin(lst) == 1)
		flag = 1;
	if (pid == 0)
	{
		if (ft_strchr(lst->split_command[0], '/') != NULL && flag == 0)
			exc_absolut_way(lst);
	
		else if (flag == 0)
			excecuting(lst, ex->tab);
	}
	else
	{
		if (flag == 1)
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

void	solo_redir_out(t_lst *lst, t_expand *ex, int i)
{
	int	pid;
	int	status;
	int fd[2];
	int	outfile;
	int	flag;

	(void) fd;
	flag = 0;
	outfile = 0;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (is_builtin(lst) == 1)
		flag = 1;
	if (pid == 0)
	{
		if (i == 2)
			outfile = open(lst->next->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i == 4)
			outfile = open(lst->next->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (outfile < 0)
		{
			printf("erreur dup\n");
		}
		//if (dup2(fd[0], STDIN_FILENO) == -1)
		//	perror("Dup");
		if (dup2(outfile, STDOUT_FILENO) == -1)
			perror("Dup");
		close(outfile);
		if (ft_strchr(lst->split_command[0], '/') != NULL && flag == 0)
			exc_absolut_way(lst);
		else if (flag == 0)
			excecuting(lst, ex->tab);
	}
	else
	{
		if (flag == 1)
			builtin(lst, ex);
		//waitpid(pid, NULL, 0);
		//if (WEXITSTATUS(pid) > 0
		//close(fd[0]);
		// close(fd[1]);
		//close(outfile);
		waitpid(pid, &status, 0);
		// Utilisez la macro WEXITSTATUS pour obtenir la valeur de retour
		//if (WIFEXITED(status))
		//printf("%d\n", status);
		g_exit_status = status / 256;
		//printf("%d\n", g_exit_status);

	}
	//printf("var globale = %d\n", g_exit_status);
}

void	solo_redir_in(t_lst *lst, t_expand *ex)
{
	int	pid;
	int	status;
	int fd[2];
	int	infile;
	int flag;

	flag = 0;
	(void) fd;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (is_builtin(lst->next) == 1)
		flag = 1;
	if (pid == 0)
	{
		infile = open(lst->split_redir[1], O_RDONLY, 0644);
		if (infile < 0)
		{
			perror("Infile");
		}
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_perror("Dup");
		close(infile);
		if (ft_strchr(lst->next->split_command[0], '/') != NULL && flag == 0)
			exc_absolut_way(lst->next);
		else if (flag == 0)
			excecuting(lst->next, ex->tab);
	}
	else
	{
		if (flag == 1)
			builtin(lst->next, ex);
		//waitpid(pid, NULL, 0);
		//if (WEXITSTATUS(pid) > 0
		//close(fd[0]);
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

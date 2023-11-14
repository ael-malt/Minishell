/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:07:53 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/14 17:42:35 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

int	is_solo_redir(t_lst *lst)
{
	int	count;

	count = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->token == 2)
			count++;
		lst = lst->next;
	}
	return (count);
}

int	is_redir(t_lst *lst)
{
	if (!lst)
		return(-1);
	if (is_heredoc(lst) == 1) // heredoc <<
		return (1);
	else if (lst->token == 2 && lst->command[0] == '>' && lst->command[1] == '>') //ajout append >>
		return (4);
	else if (lst->token == 2 && lst->command[0] == '>') // sortie
		return (2);
	else if (lst->token == 2 && lst->command[0] == '<') // entree
		return (3);
	return (0);
}

void	redir_out(int *fd, int fd_temp, t_lst *lst, t_expand *ex, int i)
{
	// ft_printf("HERE: %s\n", lst->command);
	// (void) fd;
	t_lst	*tmp_lst;
	int	outfile;

	signal(SIGQUIT, SIG_DFL);
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	if (dup2(fd_temp, STDIN_FILENO) == -1) //FD_TEMP car on recup du pipe pres
		ft_perror("Dup");
	close(fd[0]);
	// if (dup2(fd[1], STDOUT_FILENO) == -1) // ecrit dans le pipe
	// 	perror("Dup");
	close(fd_temp);
	close(fd[1]);
	if (i == 2)
		outfile = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i == 4)
		outfile = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (outfile < 0)
		printf("erreur dup\n");
	//if (dup2(fd[0], STDIN_FILENO) == -1)
	//	perror("Dup");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror("Dup");
	close(outfile);
	if (tmp_lst && is_builtin(tmp_lst) == 1)
	{
		builtin(tmp_lst, ex);
		exit(0);
	}
	else if (tmp_lst && ft_strchr(tmp_lst->split_command[0], '/') != NULL)
		exc_absolut_way(tmp_lst, ex);
	else if (tmp_lst)
		excecuting(tmp_lst, ex->tab);
}

void	solo_redir_out(t_lst *lst, t_expand *ex, int i)
{	
	int		pid;
	int		status;
	int 	fd[2];
	int		outfile;
	t_lst	*tmp_lst;
	
	(void) fd;
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	outfile = 0;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (i == 2)
			outfile = open(lst->split_redir[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i == 4)
			outfile = open(lst->split_redir[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (outfile < 0)
			printf("erreur dup\n");
		//if (dup2(fd[0], STDIN_FILENO) == -1)
		//	perror("Dup");
		if (dup2(outfile, STDOUT_FILENO) == -1)
			perror("Dup");
		close(outfile);
		if (ft_strchr(tmp_lst->split_command[0], '/') != NULL && !is_builtin(lst))
			exc_absolut_way(tmp_lst, ex);
		else if (!is_builtin(lst))
			excecuting(tmp_lst, ex->tab);
	}
	else
	{
		if (is_builtin(lst))
			builtin(tmp_lst, ex);
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

void	redir_in(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
{
	// ft_printf("HERE: %s\n", lst->command);
	// (void) fd;
	// (void) fd_temp;
	// (void) lst;
	// (void) ex;
	t_lst *tmp_lst;
	int	infile;

	signal(SIGQUIT, SIG_DFL);
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	if (dup2(fd_temp, STDOUT_FILENO) == -1) //FD_TEMP car on recup du pipe pres
		ft_perror("Dup");
	close(fd_temp);
	close(fd[0]);
	// ft_printf("content: %s\n", lst->content);
	// if (dup2(fd[1], STDOUT_FILENO) == -1) // ecrit dans le pipe
	// 	perror("Dup");
	close(fd[1]);
	infile = open(lst->split_redir[1], O_RDONLY, 0644);
	// ft_printf("infile: %s\n", lst->split_redir[1]);
	if (infile < 0)
		perror("Infile");
	if (dup2(infile, STDIN_FILENO) == -1)
		perror("Dup");
	close(infile);
	if (tmp_lst && is_builtin(tmp_lst) == 1)
	{
		builtin(tmp_lst, ex);
		exit(0);
	}
	else if (tmp_lst && ft_strchr(tmp_lst->next->split_command[0], '/') != NULL)
		exc_absolut_way(tmp_lst, ex);
	else if (tmp_lst)
		excecuting(tmp_lst, ex->tab);
}

void	solo_redir_in(t_lst *lst, t_expand *ex)
{
	int	pid;
	int	status;
	int fd[2];
	int	infile;
	t_lst *tmp_lst;

	(void) fd;
	pid = fork();
	if (pid == -1)
		perror("FORK");
	if (lst->next && !lst->token)
		lst = lst->next;
	if (lst->next && lst->next->token == 0)
		tmp_lst = lst->next;
	else if(lst->prev && lst->prev->token == 0)
		tmp_lst = lst->prev;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		infile = open(lst->split_redir[1], O_RDONLY, 0644);
		if (infile < 0)
		{
			perror("Infile");
		}
		if (dup2(infile, STDIN_FILENO) == -1)
			ft_perror("Dup");
		close(infile);
		if (ft_strchr(tmp_lst->split_command[0], '/') != NULL && !is_builtin(tmp_lst))
			exc_absolut_way(tmp_lst, ex);
		else if (!is_builtin(tmp_lst))
			excecuting(tmp_lst, ex->tab);
	}
	else
	{
		if (is_builtin(tmp_lst))
			builtin(tmp_lst, ex);
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
// void	exc_cmd2(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
// {
// 	int	outfile;

// 	outfile = open(lst->next->split_redir[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (outfile < 0)
// 	{
// 		close(fd[1]);
// 		close(fd[0]);
// 		ft_perror("Outfile");
// 	}	
// 	if (dup2(fd_temp, STDIN_FILENO) == -1)
// 		ft_perror("Dup");
// 	if (dup2(outfile, STDOUT_FILENO) == -1)
// 		ft_perror("Dup");
// 	close(fd[1]);
// 	close(fd[0]);
// 	close(outfile);
// 	close(fd_temp);
// 	if (is_builtin(lst) == 1)
// 		builtin(lst, ex);
// 	if (ft_strchr(lst->split_command[0], '/') != NULL)
// 		exc_absolut_way(lst);
// 	else
// 		excecuting(lst, ex->tab);
// }

// void	open_file(t_lst *lst)
// {
// 	if (is_redir(lst) <= 0)
// 		return ;
// 	else
// 	{
// 		if (is_redir(lst) == 4)
// 			open(,O_WRONLY | O_CREAT | O_APPEND, 0644); // mettre fd necessaire
// 		if (is_redir(lst) == 3)
// 			open(, O_RDONLY, 0644);
// 		if (is_redir(lst) == 2)
// 			open (,O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (is_redir(lst) == 1)
// 			open(O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// }

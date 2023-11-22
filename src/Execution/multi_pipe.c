/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/22 15:31:12 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

// TO-DO
// Ajouter < et << au redirections multipipes
// Gerer les redirections en dernier maillon
// Refaire mon heardoc

// void	multi_pipe(t_lst *lst, t_expand *ex)
// {
// 	int	i;
// 	int	nb_operator;
// 	int	fd[2];
// 	int	fd_temp;

// 	i = 0;
// 	fd_temp = 0;
// 	nb_operator = lst_count_pipe(lst) + lst_count_redir(lst);
	
// 	while (i <= nb_operator)
// 	{
// 		// if (i < (nb_operator))
// 		// {
// 		// 	if (lst->next && lst->token != 2 && lst->next->token == 1)
// 		// 	{
// 		// 		pipex(fd, &fd_temp, lst, ex);
// 		// 		if (lst->next != NULL && lst->next->next != NULL)
// 		// 			lst = lst->next->next;
// 		// 	}
// 		// 	else if (lst->next && (lst->next->token == 2 || lst->token == 2))
// 		// 	{
// 		// 		redirex(&fd_temp, lst, ex);
// 		// 		while (lst->next)
// 		// 		{
// 		// 			ft_printf("content: %s\n	", lst->content);
// 		// 			lst = lst->next;
// 		// 			if (lst->token == 0 || lst->token == 2)
// 		// 				break ;
// 		// 		}
// 				// if (lst->next && lst->next->token == 0 && lst->next->next 
// 				// 	&& lst->next->next->token == 1 && lst->next->next->next)
// 				// 	lst = lst->next->next->next;
// 				// else if (lst->next && lst->next->next && 
// 				// (lst->next->token == 0 || lst->next->token == 1))
// 				// 	lst = lst->next->next;
// 				// else if (lst->next)
// 				// 	lst = lst->next;
// 			// }
// 		}
// 		else
// 		{
// 			if (get_last_operator(lst) == 1)
// 				last_pipe(fd, &fd_temp, lst, ex);
// 			// else if (get_last_operator(lst) == 2)
// 			// 	last_redir(fd, &fd_temp, lst, ex);
// 		}
// 		i++;
// 	}
// 	wait(NULL);
// }

void	execute(t_lst *lst, t_expand *ex)
{
	if (is_builtin(lst) && lst_count_pipe(lst))
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else
		excecuting(lst, ex->tab);
}

void redirect(t_lst *lst, int fd_temp) {	
	int	file;

	lst = lst->next;

	file = open_redir_file(lst);
	while (lst->next && (is_redir(lst) == is_redir(lst->next) || is_redir(lst) == (is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		close(file);
		lst = lst->next;
		file = open_redir_file(lst);
	}
	printf("rex: %s %d %d\n", lst->command, lst->token, file);
	redirex(file, &fd_temp, lst);
}

void	multi_pipe(t_lst *lst, t_expand *ex)
{
	int	fd[2];
	int	pid;
	int	fd_temp;
	int	status;
	
	fd_temp = 0;
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->token == 0)
		{
			if (lst->token == 0 && lst->next && lst->next->token == 1)
				if (pipe(fd) == -1)
					perror("Pipe");
			pid = fork();
			if (pid == -1)
				perror("FORK");
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				// fprintf(stderr, "cmd: %s token: %d next: %d next_token: %d\n", lst->command ? lst->command : "no", lst->token, lst->next ? 1 : 0, lst->next ? lst->next->token : -1);

				if ((lst->prev && lst->prev->token == 1) || (lst->next && lst->next->token == 1))
				{
					// fprintf(stderr, "pipex\n");
					pipex(fd, &fd_temp, lst);
				}
				if (lst->next && lst->next->token == 2)
				{
					// fprintf(stderr, "redirect\n");
					redirect(lst, fd_temp);
				}

				// fprintf(stderr, "execute %s %d\n", lst->command, fd_temp);
				execute(lst, ex);
			}
			else
			{
				if (is_builtin(lst) && !lst_count_pipe(lst)) 
				{
					builtin(lst, ex);
					exit(0);
				}
				if (lst->next && lst->next->token == 1) {
					if (fd_temp) {
						close(fd_temp);
					}
					fd_temp = dup(fd[0]);
					close(fd[0]);
					close(fd[1]);
				}
				waitpid(pid, &status, 0);
				g_exit_status = status / 256;
			}
		}
		lst = lst->next;
	}
}

void	redirex(int file, int *fd_temp, t_lst *lst)
{
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
		/*if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}*/
	}
	else if (is_redir(lst) == 1 || is_redir(lst) == 3)
	{
		if (dup2(*fd_temp, STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}
	if (file)
		close(file);
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	if (dup2(*fd_temp, STDIN_FILENO) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return ;
	}
	close(fd[0]);
	if (lst->next && lst->next->token == 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}
	close(*fd_temp);
	close(fd[1]);
}


// void	exc_redir(int *fd, int fd_temp, t_lst *lst, t_expand *ex)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	if (dup2(fd_temp, STDIN_FILENO) == -1)
// 		ft_perror("Dup");
// 	close(fd[0]);
// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		perror("Dup");
// 	close(fd_temp);
// 	close(fd[1]);
// 	if (is_builtin(lst))
// 	{
// 		builtin(lst, ex);
// 		exit(0);
// 	}
// 	else if (ft_strchr(lst->split_command[0], '/') != NULL)
// 		exc_absolut_way(lst, ex);
// 	else
// 		excecuting(lst, ex->tab);
// }


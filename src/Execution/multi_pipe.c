/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/27 13:52:34 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

void	execute(t_lst *lst, t_expand *ex)
{
	if (is_builtin(lst) && lst_count_pipe(lst))
	{
		builtin(lst, ex);
		exit(0);
	}
	else if (is_builtin(lst))
		builtin(lst, ex);
	else if (!is_builtin(lst) &&ft_strchr(lst->split_command[0], '/') != NULL)
		exc_absolut_way(lst, ex);
	else if (!is_builtin(lst))
		excecuting(lst, ex->tab);
}

void redirect(t_lst *lst)
{	
	int	file;
	
	if (lst->next)
		lst = lst->next;
	// fprintf(stderr, "passe dans redirect %s\n", lst->command);
	file = open_redir_file(lst);
	if (file < 0)
		return (exit(0));
	while (lst->next && is_redir(lst->next) && (is_redir(lst) == is_redir(lst->next) || is_redir(lst) == (is_redir(lst->next) + 2) || is_redir(lst) == (is_redir(lst->next) - 2)))
	{
		close(file);
		if (lst->next)
			lst = lst->next;
		file = open_redir_file(lst);
		if (file < 0)
			return (exit(0));
	}
	// printf("rex: %s %d %d\n", lst->command, lst->token, file);
	redirex(file, lst);
}

static int	check_pipe_after_redir(t_lst *lst)
{
	t_lst	*tmp_lst;

	tmp_lst = 0;
	if (!lst->prev && !lst->next)
		return (0);
	if ((lst->next && lst->token == 0) || !lst_count_pipe(lst))
		tmp_lst = lst->next;
	while (tmp_lst->next && is_redir(tmp_lst))
		tmp_lst = tmp_lst->next;
	// ft_printf("ICI: %s\n", tmp_lst->content);
	if (tmp_lst->token == 1 && is_redir(tmp_lst->prev))
		return (1);
	return (0);
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
			if (lst->next && ((lst->next->token == 1) || check_pipe_after_redir(lst))) // retiré (lst->token == 0 && ) du if
				if (pipe(fd) == -1)
					perror("Pipe");
			pid = fork();
			if (pid == -1)
				perror("FORK");
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				if (lst->token == 0 && ((lst->prev && lst->prev->token == 1)
					|| (lst->next && lst->next->token == 1)
					|| check_pipe_after_redir(lst)))
					{
						pipex(fd, &fd_temp, lst);
						// fprintf(stderr, "pipex %s\n", lst->command);
					}
				if (lst->next && lst->next->token == 2)
				{
					// fprintf(stderr, "redirect %s\n", lst->command);
					redirect(lst);
				}
				execute(lst, ex);
			}
			else
			{
				if (is_builtin(lst) && !lst_count_pipe(lst)) 
					builtin(lst, ex);
				if (lst->next && (lst->next->token == 1 || check_pipe_after_redir(lst))) 
				{
					if (fd_temp)
						close(fd_temp);
					fd_temp = dup(fd[0]);
					close(fd[0]);
					close(fd[1]);
				}
				// close(fd[0]);
				// close(fd[1]);
				waitpid(pid, &status, 0);
				g_exit_status = status / 256;
			}
		}
		// printf("ffgff\n");
		// is_solo_heredoc(lst, fd_temp);
		if (lst->token == 2 && is_redir(lst) == 1 && lst->prev == NULL && lst->next == NULL) // heredox seul
			redirect(lst);
		lst = lst->next;
	}
}

void	redirex(int file, t_lst *lst)
{
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		// fprintf(stderr, "redirex STDOUT: %s\n", lst->command);
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 3 || (lst->next && is_redir(lst) == 1) || is_redir(lst) == 1)//lst->next pour heredoc seul
	{
		// fprintf(stderr, "redirex STDIN: %s\n", lst->command);
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	if (file)
		close(file);
	// close(fd[0]);
	// close(fd[1]);
	if (lst->next && lst->next->token == 2)
	{
		// fprintf(stderr, "redir dif\n");;
		redirect(lst);
	}
	
}

void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	
	// if (lst->next && lst->next->token == 1)
	if (lst->prev && lst->prev->token == 1)
	{
		// fprintf(stderr, "pipex STDIN: %s\n", lst->command);
		if (dup2(*fd_temp, STDIN_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}	
	close(fd[0]);
	if (lst->next && (lst->next->token == 1 || check_pipe_after_redir(lst)))
	{
		// fprintf(stderr, "pipex STDOUT: %s\n", lst->command);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			mini_perror(PIPERR, NULL, 1);
			return ;
		}
	}
	close(*fd_temp);
	close(fd[1]);
}

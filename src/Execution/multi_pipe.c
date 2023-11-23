/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:24:15 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/23 17:22:50 by ael-malt         ###   ########.fr       */
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
		exit(0);
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
	printf("rex: %s %d %d\n", lst->command, lst->token, file);
	redirex(file, lst);
	//PEUT ETRE METTRE CONDITION REDIR DIFF POUR OUVRIR
	// if (is_redir(lst->next) < 0)
	// 	printf("redir\n");
}
// PROB = lors redir si redir qui se suivent font diff alors ca ne fait pas la derniere redir
// EX : ls | wc -l > outt << fg = n'ouvre pas le heredoc ; bash = ouvre heredoc et met res dans outt
// heredoc seul fonctionne ; PROB avec ls devant aussi sauf wc -l << heredoc ou cat
// mais avec un pipe ou plusieurs avant, il ne fonctionne pas 
// EX : ls | wc -l << heredoc ls se fait dans heredoc, il detecte la fin de la liste et ca ferme le heredox car ligne null alors erreur signaux et apres wc renvoi 0
// PROB = cat < in | wc -l inprime ce qu(il yb a dans in dans stdout standart et | pas crer et wc -l recoit rien)
// redir inversé
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
			if (lst->next && lst->next->token == 1) // retiré (lst->token == 0 && ) du if
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
					// ft_printf("ici\n");
				}
				if (lst->next && lst->next->token == 2)
				{
					// fprintf(stderr, "command: %s\n", lst->command);
					// fprintf(stderr, "redirect\n");
					redirect(lst);
				}
				// fprintf(stderr, "execute %s %d\n", lst->command, fd_temp);
				execute(lst, ex);
				// printf("erer\n");
			}
			else
			{
				// if (is_builtin(lst) && !lst_count_pipe(lst)) 
				// 	builtin(lst, ex);
				if (lst->next && lst->next->token == 1) {
					if (fd_temp) {
						close(fd_temp);
					}
					fd_temp = dup(fd[0]);
					close(fd[0]);
					close(fd[1]);
				}
				close(fd[0]);
				close(fd[1]);
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
// void	is_solo_heredoc(t_lst *lst, int fd_temp) // fonctione pas car message erreur fin heredoc
// {
// 	if (lst->token == 2 && is_redir(lst) == 1 && lst->prev == NULL && lst->next == NULL)
// 	{
// 		redirect(lst, fd_temp);
// 	}
// }

void	redirex(int file, t_lst *lst)
{
	if ((is_redir(lst) == 2 || is_redir(lst) == 4))
	{
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
	}
	else if (is_redir(lst) == 3 || (lst->next && is_redir(lst) == 1) || is_redir(lst) == 1) //lst->next pour heredoc seul
	{
		printf("std in = file\n");
		if (dup2(file, STDIN_FILENO) == -1)
		{
			mini_perror(DUPERR, NULL, 1);
			return ;
		}
		// if (lst->next && lst->next->token == 1) // ajout pour pipe after  redir
		// {
			
		// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
		// 	{
		// 		mini_perror(PIPERR, NULL, 1);
		// 		return ;
		// 	}
		// }
	}
	if (file)
		close(file);
	if (lst->next && lst->next->token == 2)
	{
		printf("redir dif\n");
		redirect(lst);
	}
	
}
void	pipex(int *fd, int *fd_temp, t_lst *lst)
{
	// fprintf(stderr, "command: %s\n", lst->command);

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

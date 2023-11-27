/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:00:00 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/27 11:03:47 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

int	is_heredoc(t_lst *lst)
{
	// ft_printf("content = %s\n", lst->command);
	if (lst->token == 2 && lst->command[0] == '<' && lst->command[1] == '<')
		return (1);
	return (0);
}

int	count_heredoc(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->token == 2 && lst->command[0] == '<' && lst->command[1] == '<')
			i++;
		lst = lst->next;
	}
	return (i);
}

void	heredoc_signal(int fd, int i)
{
	if (i == 1)
		close(fd);
	else
	{
		// ft_printf("HERE\n");
		ft_putendl_fd("minishell: warning:\
 here-document delimited by end-of-file", 2);
		unlink(".tmp");
		close(fd);
		//exit(0);
	}
}

int	is_heredoc_limiter_valid(t_lst *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (-1);
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		if (lst->token == 2 && lst->split_redir[1] != NULL)
		{
			// printf("%s\n", lst->split_redir[1]);
			while (lst->split_redir[1][i])
			{
				if (lst->split_redir[1][i] == '|' || lst->split_redir[1][i] == '<' || lst->split_redir[1][i] == '>' || lst->split_redir[1][i] == '&' || lst->split_redir[1][i] == '#')
				{
					mini_heardoc_error(OPERROR, &lst->split_redir[1][i], 2);
					return (1);
				}
				i++;
			}
		}
		lst = lst->next;
	}
	return (0);
}

void	mini_heredoc(t_lst *lst)
{
	char	*line;
	int		fd;

	if (is_heredoc_limiter_valid(lst))
		return ;
	g_exit_status = 0;
	line = NULL;
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// fprintf(stderr, "HEREDOC fd: %d\n", fd);
	// if (fd == -1)
	// 	mini_perror(NDIR, lst->split_redir[1], 1); // si decomment ls > out << heredox envoi err open
	while (1)
	{
		// printf("coucou\n");
		line = readline("> ");
		if (g_exit_status == 130)
			return heredoc_signal(fd, 1);
		if (line == NULL)
		{
			// printf("here\n");
			heredoc_signal(fd, 2);
			break ;
		}
		if (lst->split_redir[1] && strcmp(line, lst->split_redir[1]) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	if (line != NULL)
		free(line);
	close(fd);
}

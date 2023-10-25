/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:00:00 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/25 19:40:11 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

int	is_heredoc(t_lst *lst)
{
	// ft_printf("content = %s\n", lst->command);
	if (lst->token == 2 && lst->command[0] == '<' && lst->command[1] == '<')
		return (1);
	return (0);
}

static void	heredoc_signal(int fd, int i)
{
	if (i == 1)
		close(fd);
	else
	{
		ft_printf("HERE\n");
		ft_putendl_fd("minishell: warning:\
 here-document delimited by end-of-file", 2);
		unlink(".tmp");
		close(fd);
		// exit(0);
	}
}

void	mini_heredoc(t_lst *lst)
{
	char	*line;
	int		fd;
	char	*limiter;
	char	**split;

	g_exit_status = 0;
	line = NULL;
	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		perror("open");
	while (1)
	{
		if (g_exit_status == 130)
			return (heredoc_signal(fd, 1));
		line = readline(">");
		if (line == NULL)
			heredoc_signal(fd, 2);
		else
		{
			split = ft_split(lst->command, ' ');
			limiter = ft_strdup(split[1]);
			if (strcmp (line, limiter) == 0)
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	if (line != NULL)
		free(line);
	ft_free_matrix(&split);
	free(limiter);
	close(fd);
}

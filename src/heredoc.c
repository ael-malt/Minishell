/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:00:00 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/24 18:16:34 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;
int	is_heredoc(t_lst *lst)
{
	if (lst->token == 2 && lst->content[0] == '<' && lst->content[1] == '<')
		return (1);
	return (0);
}

int	mini_heredoc(t_lst *lst)
{
	int	fd[2];
	// char
	// g_exit_status = 0;
	if(pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}

	(void) lst;
	// ft_printf("here\n");
	return (0);
}

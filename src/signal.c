/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:44:19 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/23 15:42:18 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	g_exit_status;

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		g_exit_status = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// exit(0);
	}
	// else if (signal == SIGQUIT)
	// {
		// rl_on_new_line();
		// rl_redisplay();
	// }z
}

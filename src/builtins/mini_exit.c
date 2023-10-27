/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:51 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/27 14:12:00 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

int mini_exit(char **split_command)
{
	int n;
	int i;
	int is_num;

	n = 0;
	i = 1;
	is_num = 1;
	ft_printf("exit\n");
	if (split_command[1] && split_command[2])
		return (ft_putendl_fd("Minishell: exit: too many arguments", 2));
	if (split_command[1])
	{
		while (split_command[1][i])
		{
			if (!ft_isdigit(split_command[1][i]) || split_command[1][0] != '-')
				is_num = 0;
			i++;
		}
		if (is_num)
		{
			n = ft_atoi(split_command[1]);
			if (n >= 0 && n <= 255)
				g_exit_status = n;
			else
				g_exit_status = n % 256;
		}
		else
		{
			ft_putstr_fd("minishell: exit: numeric argument required: ", 2);
			ft_putendl_fd(split_command[1], 2);
			g_exit_status = 2;
		}
	}
	exit(g_exit_status);
	return (1);
}

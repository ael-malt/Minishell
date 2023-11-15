/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:40:59 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/24 15:41:10 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_echo(t_lst *lst)
{
	int	i;
	int	n;
	int	j;
	
	i = 1;
	n = 0;
	while (lst->split_command[i] && !ft_strncmp(lst->split_command[i], "-n", 2))
	{
		j = 1;
		while(lst->split_command[i][++j] == 'n');
		if (lst->split_command[i][j - 1] && lst->split_command[i][j] == '\0')
		{
			n = 1;
			i++;
		}
		else
			break ;
	}
	while (lst->split_command && lst->split_command[i])
	{
		ft_printf("%s",lst->split_command[i]);
		if (lst->split_command[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!n)
		ft_printf("\n");
	return (0);
}

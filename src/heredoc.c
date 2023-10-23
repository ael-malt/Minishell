/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:00:00 by ael-malt          #+#    #+#             */
/*   Updated: 2023/10/23 18:03:26 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_heredoc(t_lst *lst)
{
	int	is_redirect;

	is_redirect = 0;
	if (lst->token == 2)
		is_redirect = 1;
	// ft_printf("%s\n", lst->command);
	return (0);
}

int	mini_heredoc(t_lst *lst)
{
	(void) lst;
	return (0);
}

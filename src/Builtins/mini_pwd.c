/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:39:25 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/28 17:03:54 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:39:25 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/28 17:28:39 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (buf)
	{
		ft_printf("%s\n", buf);
		free(buf);
	}
	return (0);
}

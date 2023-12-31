/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:44:32 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 14:46:22 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen(s) + 1);
	}
	return (0);
}

/*int	main(void)
{
	char	s[] = "coucou";
	ft_putendl_fd(s, 1);
	return (0);
}*/

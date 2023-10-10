/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:44:32 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/29 16:06:20 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	end;
	int		i;

	end = '\n';
	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			write (fd, &s[i], 1);
			i++;
		}
		write (fd, &end, 1);
	}
}

/*int	main(void)
{
	char	s[] = "coucou";
	ft_putendl_fd(s, 1);
	return (0);
}*/

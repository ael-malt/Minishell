/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:25:25 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:30:06 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_len_u(unsigned int u)
{
	int	count;

	count = 0;
	while (u != 0)
	{
		count++;
		u /= 10;
	}
	return (count);
}

char	*ft_unsigned_itoa(unsigned int i)
{
	int		count;
	char	*u;

	count = ft_len_u(i);
	u = malloc(count + 1);
	if (!u)
		return (NULL);
	u[ft_len_u(i)] = '\0';
	while (i > 0)
	{
		u[count - 1] = i % 10 + 48;
		i /= 10;
		count--;
	}
	return (u);
}

int	ft_put_u(unsigned int i)
{
	int		count;
	char	*u;

	count = 0;
	if (i == 0)
		count += write(1, "0", 1);
	else
	{
		u = ft_unsigned_itoa(i);
		count += ft_putstr(u);
		free(u);
	}
	return (count);
}

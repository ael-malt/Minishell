/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:11 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:22:33 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_put_hexa(unsigned int n, const char flag)
{
	if (n >= 16)
	{
		ft_put_hexa((n / 16), flag);
		ft_put_hexa((n % 16), flag);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (flag == 'x')
				ft_putchar(n - 10 + 'a');
			else if (flag == 'X')
				ft_putchar(n - 10 + 'A');
		}
	}
	return (ft_hexa_size(n));
}

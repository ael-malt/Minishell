/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:08:24 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:34:51 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_putchar(int c)
{	
	write(1, &c, 1);
	return (1);
}

int	ft_putpourcent(void)
{
	ft_putchar('%');
	return (1);
}

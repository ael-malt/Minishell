/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:19:44 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:20:07 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_hexa_size(unsigned int n)
{
	int	size;

	size = 0;
	while (n != 0)
	{
		size++;
		n = n / 16;
	}
	return (size);
}

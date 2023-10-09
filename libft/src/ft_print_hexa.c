/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:22:54 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:23:17 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_print_hexa(unsigned int n, const char flag)
{
	int	count;

	count = 0;
	if (n == 0)
		count += write(1, "0", 1);
	else
		count += ft_put_hexa(n, flag);
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_void_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:37:19 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:36:04 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	hexavoid_len(uintptr_t n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

int	ft_put_hexavoid(uintptr_t n)
{
	if (n >= 16)
	{
		ft_put_hexavoid(n / 16);
		ft_put_hexavoid(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
			ft_putchar(n - 10 + 'a');
	}
	return (hexavoid_len(n));
}

int	ft_print_voidtohexa(unsigned long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count += write(1, "(nil)", 5);
	else
	{	
		count = write(1, "0x", 2);
		ft_put_hexavoid(n);
		count += hexavoid_len(n);
	}
	return (count);
}
/*hexavoid_len = longueur pour hexavoid
ft_put_hexavoid = calcul de hexavoid
int	ft_print_hexa = imprimer hexavoid
*/

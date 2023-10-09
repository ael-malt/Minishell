/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:24:34 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:24:55 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	a;
	int		i;
	int		compteur;

	i = 0;
	compteur = 0;
	va_start(a, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			compteur += ft_execut_flag(s[i + 1], a);
			i++;
		}	
		else
			compteur += ft_putchar(s[i]);
		i++;
	}
	va_end(a);
	return (compteur);
}

int	ft_execut_flag(const char flag, va_list a)
{
	int	compteur;

	compteur = 0;
	if (flag == 'c')
		compteur += ft_putchar(va_arg(a, int));
	else if (flag == 's')
		compteur += ft_putstr(va_arg(a, char *));
	else if (flag == 'p')
		compteur += ft_print_voidtohexa(va_arg(a, unsigned long long));
	else if (flag == 'd' || flag == 'i')
		compteur += ft_print_nbr(va_arg(a, unsigned int));
	else if (flag == 'u')
		compteur += ft_put_u(va_arg(a, unsigned int ));
	else if (flag == 'x' || flag == 'X')
		compteur += ft_print_hexa(va_arg(a, unsigned int), flag);
	else if (flag == '%')
		compteur += ft_putpourcent();
	return (compteur);
}

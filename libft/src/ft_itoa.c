/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:30:22 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:09:37 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_size_str(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	nb = 0;
	if (n < 0)
	{
		i++;
		nb = n * -1;
	}
	else
		nb = n;
	while (nb != 0 || i == 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	size_t			i;
	size_t			j;
	char			*str;

	j = ft_size_str(n);
	nb = n;
	i = 0;
	str = malloc(j + 1);
	if (!str)
		return (0);
	if (n < 0)
	{
		str[i] = '-';
		nb *= -1;
		i++;
	}
	str[j] = '\0';
	while (j > i)
	{
		j--;
		str[j] = nb % 10 + 48;
		nb /= 10;
	}
	return (str);
}

/*int	main(void)
{
	int	n = -2147483648;
	int	n1 = -12;
	int	n2 = 198;
	int     n3 = 2147483647;
	printf("%s\n", ft_itoa(n));
	printf("%s\n", ft_itoa(n1));
	printf("%s\n", ft_itoa(n2));
	printf("%s\n", ft_itoa(n3));
	return (0);
}*/

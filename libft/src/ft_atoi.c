/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:52:41 by lazanett          #+#    #+#             */
/*   Updated: 2023/05/03 16:02:32 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

long long	ft_atoi(const char *nptr)
{
	long	n;
	int		i;
	int		signe;

	i = 0;
	signe = 1;
	n = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + nptr[i] - '0';
		i++;
	}
	return (n * signe);
}

/*int	main(void)
{
	const char	*nptr = " ---+--1";
	printf("%d\n", ft_atoi(nptr));
	if(atoi(nptr) == ft_atoi(nptr))
		printf("%s\n","OK");
        return (0);
}*/

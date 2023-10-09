/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:53:31 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 18:05:13 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	i = 0;
	s = (char *)src;
	d = (char *)dest;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}	
	return (dest);
}

/*int     main(void)
{
	char dest [] = "Salutation";
	const char  src[] = "hello ca va ?";
	char dest1[] = "Salutation";
	const char src1[] = "hello ca va ?";
	size_t n = 4;
	printf("%s\n", (char *)ft_memmove(dest, src, n));
	printf("%s\n",(char *)memmove(dest1, src1, n));
	if(memmove(dest, src, n) == ft_memmove(dest, src, n))
		printf("%s\n","OK");
        return (0);
}*/

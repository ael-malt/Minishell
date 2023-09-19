/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:17:19 by lazanett          #+#    #+#             */
/*   Updated: 2023/05/03 16:03:16 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest != src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*int     main(void)
{
	char dest [] = "Salutation";
	const char  src[] = "hello";
	size_t n = 2;
	printf("%s\n", (char *)ft_memcpy(dest, src, n));
	if(memcpy(dest, src, n) == ft_memcpy(dest, src, n))
		printf("%s\n","OK");
        return (0);
}*/

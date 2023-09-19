/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:51:08 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:50 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}

/*int     main(void)
{
	char dst[] = "Lara";
	const char src[] = "Hello";
	size_t size = 5;
	printf("%ld\n", ft_strlcpy(dst, src, size));
	if(strlcpy(dst, src, size) == ft_strlcpy(dst, src, size))
		printf("%s\n","OK");
        return (0);

}*/

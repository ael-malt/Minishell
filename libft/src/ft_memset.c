/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:38:16 by lazanett          #+#    #+#             */
/*   Updated: 2023/05/03 16:03:38 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

/*int     main(void)
{
	char s[] = "Salutation";
	int c = '.';
	size_t n = 7;
	printf("%s\n", (char *)ft_memset(s, c, n));
	if(memset(s, c, n) == ft_memset(s, c, n))
		printf("%s\n","OK");
        return (0);
}*/

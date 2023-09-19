/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:49:44 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:30 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *)s;
	while (i < n)
	{
		if (string[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const char s[] = "Salutation";
	int	c = 'a';
	size_t n = 5;
	printf("%s\n",(char *)ft_memchr(s, c, n));
	if(memchr(s, c, n)  == ft_memchr(s, c, n))
		printf("%s\n","OK");
        return (0);
}*/

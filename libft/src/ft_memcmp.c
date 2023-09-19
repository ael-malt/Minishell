/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:26:03 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:31 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/*int     main(void)
{
	const char s1[] = "Salutation";
	const char s2[] = "Salut";
	size_t n = 7;
	printf("%d\n", memcmp(s1, s2, n));
	printf("%d\n", ft_memcmp(s1, s2, n));
	if(memcmp(s1, s2, n) == ft_memcmp(s1, s2, n))
		printf("%s\n","OK");
        return (0);

}*/

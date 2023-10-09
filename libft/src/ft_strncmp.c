/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:37:32 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:52 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && 0 < n)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*int     main(void)
{
	const char s1[] = "Salutation";
	const char s2[] = "Salut";
	size_t n = 7;
	printf("%d\n", ft_strncmp(s1, s2, n));
	if(strncmp(s1, s2, n) == ft_strncmp(s1, s2, n))
		printf("%s\n","OK");
        return (0);

}*/

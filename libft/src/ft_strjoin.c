/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:18:30 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/29 15:57:45 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!str)
			return (NULL);
		while (s1[i] != '\0')
			str[j++] = s1[i++];
		i = 0;
		while (s2[i] != '\0')
			str[j++] = s2[i++];
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}

/*int	main(void)
{
	const char s1[] = "coucou";
	const char s2[] = "Lara";
	printf("%s\n%s\n", s1, s2);
	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:29:56 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:58 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*alloc(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;

	if (!s)
		return (NULL);
	if (start > ft_strlen (s))
		start = ft_strlen (s);
	if (start + len > ft_strlen (s))
		len = ft_strlen (s) - start;
	string = alloc(s, start, len);
	return (string);
}

/*int	main(void)
{
	char const s[] = "Salutations";
	unsigned int start = 2;
	size_t len = 7;
	printf ("%s\n", ft_substr(s, start, len));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:22:27 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:47 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	i;
	int		len;

	len = 0;
	while (s[len] != '\0')
		len++;
	if (!s)
		return (NULL);
	copy = (char *)malloc(sizeof(*s) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

/*int	main(void)
{
	const char s[] = "Lara ca va?";
	printf("%s\n", strdup(s));
	printf("%s\n", ft_strdup(s));
        return (0);
}*/

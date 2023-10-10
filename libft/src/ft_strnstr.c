/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:51:15 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/28 12:45:51 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lenbis;

	i = 0;
	lenbis = ft_strlen((char *)little);
	if (!big && len == 0)
		return (NULL);
	if (lenbis == 0)
		return ((char *)big);
	while (big[i] && len)
	{
		if (ft_strncmp((char *)&big[i], (char *)little, lenbis) == 0
			&& lenbis <= len)
		{
			if ((i + lenbis) > len)
				return (NULL);
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
/*int     main(void)
{
	const char big[] = "Salutation";
	const char little[] = "ta";
	size_t len = 7;
	printf("%s\n", ft_strnstr(big, little, len));
	if(strnstr(big, little, len) == ft_strnstr(big, little, len))
		printf("%s\n","OK");
        return (0);
}*/

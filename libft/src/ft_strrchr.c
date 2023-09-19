/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:45:20 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 18:12:09 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/*int	main(void)
{
	const char s[] = "Salutation";
	int	c = 'a';
	printf("%s\n",ft_strrchr(s, c));
	if(strrchr(s, c)  == ft_strrchr(s, c))
		printf("%s\n","OK");
        return (0);
}*/

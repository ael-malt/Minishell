/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:07:02 by lazanett          #+#    #+#             */
/*   Updated: 2023/05/09 11:03:28 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

/*int	main(void)
{
	const char s[] = "Salutation";
	int	c = 'a';
	printf("%s\n",ft_strchr(s, c));
	if(strchr(s, c)  == ft_strchr(s, c))
		printf("%s\n","OK");
        return (0);
}*/

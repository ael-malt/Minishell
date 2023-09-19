/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:47:39 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:23 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

/*int	main(void)
{
        char str[5] = "salut";
        bzero(str+2, 2);
        printf("%s\n",str);

        char s[5] = "salut";
        ft_bzero(s+2, 2);
        printf("%s\n",s);
	return (0);
}*/

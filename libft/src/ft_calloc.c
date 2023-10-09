/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:33:49 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/29 10:23:43 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (size == 0 || nmemb == 0)
		return (malloc (0));
	if (nmemb < (SIZE_MAX / size))
	{
		str = malloc(nmemb * size);
		if (!str)
			return (NULL);
		ft_bzero(str, size * nmemb);
		return (str);
	}
	return (NULL);
}

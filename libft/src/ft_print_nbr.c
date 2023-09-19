/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:13:36 by lazanett          #+#    #+#             */
/*   Updated: 2023/01/28 17:16:13 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_print_nbr(unsigned int n)
{
	int		res;
	char	*temp;

	temp = ft_itoa(n);
	res = ft_putstr(temp);
	free(temp);
	return (res);
}

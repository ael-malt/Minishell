/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:04:51 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 18:25:11 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*elem;

	if (!del || !lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		elem = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = elem;
	}
}

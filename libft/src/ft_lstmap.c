/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:00:39 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 18:30:26 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*content;
	t_list	*conteneur;
	t_list	*end;

	end = NULL;
	if (!f)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		conteneur = ft_lstnew(content);
		if (!conteneur)
		{
			if (del)
			{
				del(conteneur);
				ft_lstclear(&end, del);
				return (NULL);
			}
		}
		ft_lstadd_back(&end, conteneur);
		lst = lst->next;
	}
	return (end);
}

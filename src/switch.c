/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:20:08 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/03 17:53:12 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replace(t_expand *ex, char *s)
{
	int	len_com;
	len_com = ft_strlen(s);
	ex->new_command = malloc(sizeof (char) *(len_com - ex->len_var) + ex->replace); // + 1?
	
}

// prendre tout avant $ dans commande de base 
// rajouter replace
// et rajouter la suite de la commande apres variable env
// voir si marche avec plusieurs varibale d'env
// guillemet a prendre en compte
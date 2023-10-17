/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:49:06 by marvin            #+#    #+#             */
/*   Updated: 2023/10/13 10:49:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// "$USERR" =        ||   "$USERR"
// $USERR =         ||    $USERR  
// "'$USERRR'" = ''     || '$USERR'
// '"$USERR"' = "$USERR"    ||  "$USERR" ==== OK
// '$USERR' = $USERR        ||  $USERR ==== OK

// int env_is_ok(t_expand *ex, t_lst * lst)
// {
//     int i;

//     i = 0;
//     while (s[i])
//     {

//     }
//     return (0);
// }
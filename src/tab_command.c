/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:28:51 by marvin            #+#    #+#             */
/*   Updated: 2023/09/25 10:28:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	**get_str(char *s) //commande a mettre dans un maillon; si nv commande aller vers la droite
// {
// 	int	i;
// 	int j;
// 	int k;
// 	char **tab;
// 	char *temp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	tab = malloc(sizeof(char *) * word_count(s));
// 	while (limiteur(s[i]) != 1 || s[i])
// 	{
// 		if (s[i] && s[i] == ' ')
// 			i++;
// 		if (limiteur(s[i]) != 1 && s[i] && s[i] != ' ')
// 		{
// 			temp = malloc(sizeof (char) * len_word_count(&s[i]));
// 			while (s[i] && s[i] != ' ')
// 			{
// 				temp[k] = s[i];
// 				i++;
// 				k++;
// 			}
// 			tab[j] = strdup(temp);
// 			printf("%s\n", tab[j]);
// 			//printf("%c\n", s[i]);
// 			j++;
// 			k = 0;
// 			free(temp);
// 			//temp = NULL;
// 		}
// 		if (limiteur(s[i]) == 1)
// 		{
// 			break;
// 			return (tab);
// 		}	
// 		if (s[i] == '\0')
// 			return (tab);
// 	}
// 	return (tab);
// }

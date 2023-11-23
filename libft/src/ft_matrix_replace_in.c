/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_replace_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:57:02 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/23 15:09:42 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
	char	**tmp_m;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	tmp_m = ft_calloc(ft_matrixlen(*big) + ft_matrixlen(small), sizeof(char *));
	while (tmp_m && big[0][++i])
	{
		if (i != n)
			tmp_m[++k] = ft_strdup(big[0][i]);
		else
		{
			while (small && small[++j])
				tmp_m[++k] = ft_strdup(small[j]);
		}
	}
	ft_free_matrix(big);
	*big = tmp_m;
	return (*big);
}

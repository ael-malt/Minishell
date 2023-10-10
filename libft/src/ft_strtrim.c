/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:38:17 by lazanett          #+#    #+#             */
/*   Updated: 2022/11/24 17:30:57 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trim;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] != '\0' && is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		end--;
	str_trim = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str_trim)
		return (NULL);
	i = 0;
	while (start < end)
		str_trim[i++] = s1[start++];
	str_trim[i] = '\0';
	return (str_trim);
}

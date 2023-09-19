/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:54:53 by lazanett          #+#    #+#             */
/*   Updated: 2023/07/20 14:49:11 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin_gnl(char *line, char *buf)
{
	char	*tab;
	char	*new;
	int		size;
	int		i;

	i = 0;
	size = (ft_strlen_gnl(line) + ft_strlen_gnl(buf));
	tab = malloc (sizeof(char) * (size + 1));
	new = tab;
	if (!new)
		return (NULL);
	while (line && line[i])
	{
		tab[i] = line[i];
		i++;
	}
	while (*buf)
	{
		tab[i++] = *buf++;
	}
	tab[size] = '\0';
	free (line);
	return (new);
}

char	*ft_strchr_gnl(char *line, int c)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] != (char)c))
	{
		i++;
	}
	if (line[i] == (char)c)
		return ((char *)line + i);
	else
		return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

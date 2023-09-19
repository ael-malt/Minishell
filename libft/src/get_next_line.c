/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:54:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/07/20 14:48:59 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*get_next_line(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_read_line(fd, line, buf[fd]);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*ft_read_line(int fd, char *line, char *buf)
{
	int	ret;

	ret = 1;
	line = ft_strjoin_gnl(line, buf);
	while (ret > 0 && !ft_strchr_gnl(line, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		line = ft_strjoin_gnl(line, buf);
		if (line == NULL)
			return (NULL);
	}
	if (ft_strchr_gnl(line, '\n'))
	{	
		buf = ft_getlast_line(line, buf);
		line = ft_check_line(line);
	}	
	return (line);
}

char	*ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i++;
	line [i] = '\0';
	return (line);
}

char	*ft_getlast_line(char *line, char *buf)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i++;
	j = 0;
	while (line[i])
	{
		buf[j] = line[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	return (buf);
}

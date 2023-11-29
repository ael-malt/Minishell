/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:05:29 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/29 18:19:22 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_countchar(char *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

void	print_big_minishell()
{
	ft_printf("\033[2J\033[1;1H");
	ft_printf("\x1b[31;1mMMM      MMM  IIIIIIIIIIII NNNNN    NNN IIIIIIIIIIII SSS\
SSSSSSSSS HHH      HHH EEEEEEEEEEEE LLL          LLL         \n");
	ft_printf("\x1b[33mM|\\MM  MM/|M  IIII\\II/IIII N|¯\\NN   N|N IIII\\II/IIII\
 SS/¯SSSSSSSS H|H      H|H EE/EEEEEEEEE L|L          L|L         \n");
	ft_printf("\x1b[32mM|M\\MMMM/M|M      I||I     N|NN\\N   N|N     I||I     S\
¦SS         H|H      H|H E|E          L|L          L|L         \n");
	ft_printf("\x1b[32mM|MM\\/\\/MM|M      I||I     N|N N\\N  N|N     I||I     \
SS\\SSSSSSSSS H|HHHHHHHH|H E¦\\EEEEEEE   L|L          L|L         \n");
	ft_printf("\x1b[36mM|M      M|M      I||I     N|N  N\\N N|N     I||I     SS\
SSSSSS\\SSS H|HHHHHHHH|H E¦/EEEEEEE   L|L          L|L         \n");
	ft_printf("\x1b[36mM|M      M|M      I||I     N|N   N\\NN|N     I||I       \
      S¦SS H|H      H|H E|E          L|L          L|L         \n");
	ft_printf("\x1b[34mM|M      M|M  IIII/II\\IIII N|N    N\\_/N IIII/II\\IIII \
SSSSSSSS_/SS H|H      H|H EE\\EEEEEEEEE L\\_LLLLLLLLL L\\_LLLLLLLLL\n");
	ft_printf("\x1b[35mMMM      MMM  IIIIIIIIIIII NNN     NNNN IIIIIIIIIIII SSS\
SSSSSSSSS HHH      HHH EEEEEEEEEEEE LLLLLLLLLLLL LLLLLLLLLLLL\n\x1b[0m");
}

char	*get_line_info(t_expand *ex)
{
	char	*tmp;
	char	*tmp2;
	char	*pwd;
	int		i[3];

	pwd = NULL;
	i[0] = export_vintab("PWD=", ex->tab);
	if (i[0] == -1)
		pwd = getcwd(pwd, 0);
	else
		pwd = &ex->tab[i[0]][4];
	i[1] = unset_vintab("USER", ex->tab);
	i[2] = 0;
	if (i[1] != -1)
	{
		while (ex->tab[i[1]][i[2]++] != '=');
		tmp = &ex->tab[i[1]][i[2]];
	}
	else
		tmp = ft_strdup("guest");
	tmp2 = ft_strjoin(GREEN, tmp);
	if (i[2] == 0)
		free(tmp);
	tmp = ft_strjoin(tmp2, "@Minishell");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, DEFAULT);
	free(tmp);
	tmp = ft_strjoin(tmp2, ":");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, BLUE);
	free(tmp);
	tmp = ft_strjoin(tmp2, pwd);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, DEFAULT);
	free(tmp);
	tmp = ft_strjoin(tmp2, "$ ");
	free(tmp2);
	if (i[0] == -1)
		free(pwd);
	return (tmp);
}

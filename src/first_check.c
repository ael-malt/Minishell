/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:43 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/12 18:14:44 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_char(char *s) // chercher ';' et '\'
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' || s[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	search_quote(char *s) // check des guillements
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		// Si c'est une SQUOTE
		if (flag == 0 && s[i] == '\'')// C'est l'ouvrante
			flag = 1;
		else if (flag == 1 && s[i] == '\'')// c'est la fermante
			flag = 3;
		// Si c'est une DQUOTE
		else if (flag == 0 && s[i] == '\"')// C'est l'ouvrante
			flag = 2;
		else if (flag == 2 && s[i] == '\"')// c'est la fermante
			flag = 0;
		i++;
	}
	//printf("%d = flag\n", flag);
	if (flag != 0)
		return (1);
	return (0);
}

void	search_quote_in_split(t_lst *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while(lst)
	{
		if (lst->token == 0)
		{
			while (lst->split_command[i])
			{
				//printf("command[%i] av = %s\n", i, lst->split_command[i]);
				if (lst->split_command[i][0] == '\"' || lst->split_command[i][0] == '\'')
					lst->split_command[i] = supp_quote(lst->split_command[i]);
				//printf("command[%i] ap = %s\n", i, lst->split_command[i]);
				i++;
			}
		}
		lst = lst->next;
	}
}

char	*supp_quote(char *s)
{
	int	i;
	int	index;
	int	len;
	char *rep;

	len = 0;
	index = 0;
	while (s[len])
		len++;
	rep = malloc(sizeof (char) * len + 1);
	if (!rep)
		return (NULL);
	i = 0;
	while (s[i]) // car len == " '"
	{
		if ((i == (len - 1) && s[i] == '\'') || (i == (len - 1) && s[i] == '\"'))
		{
			i++;
			if (s[i] == '\0')
				break;
		}
		if ((i == 0 && s[i] == '\'') || (i == 0 && s[i] == '\"'))
			i++;
		rep[index] = s[i];
		i++;
		index++;
	}
	rep[index] = '\0';
	return (rep);
}

// si pas entre ' ' && ca existe pas alors rien renvoyer
// si c'est entre ' ' alors ne pas imprimer les ' ' qui entour varibale d'env
// si c'est entre '" "' alors et pas imprimer les ' ' mais imprimer les " " qui entour varibale d'env
// si entre ' ' il y a " " afficher les ' '
// si " " afficher les ' ' mais supp les " " de base
// char *get_line_since_quote(char *line)
// {
// 	int	i;
// 	int start;
// 	int end;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			start = i;
// 			i++;
// 			while (line[i] && line[i] != '\'')
// 				i++;
// 			end = i;
// 			line = ft_new_line1(line, start, end);
// 		}
// 		if (line[i] == '\"')
// 		{
// 			start = i;
// 			i++;
// 			while (line[i])
// 			{
// 				if (line[i] == '\"')
// 					end = i;
// 				i++;
// 				//printf ("%d\n", end);
// 			}
// 			line = ft_new_line2(line, start, end);
// 			// while (start <= end)
// 			// {}
// 			// i = - 1;
// 		}
// 		i++;
// 	}
// 	return (line);
// }

// char *ft_new_line1(char *line, int start, int end)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	char	*new_line;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	if (line != NULL)
// 		len = ft_strlen(line);
// 	new_line = malloc(sizeof (char) * len);
// 	if (!new_line)
// 		return (NULL);
// 	while (new_line[i])
// 	{
// 		new_line[i] = '\0';
// 		i++;
// 	}
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (i == start || i == end || line[i] == '\'')
// 		{
// 			i++;
// 			while (line[i] == '\'')
// 				i++;
// 		}
// 		new_line[j] = line[i];
// 		i++;
// 		j++;
// 	}
// 	i = 0;
// 	free(line);
// 	return (new_line);
// }

// char *ft_new_line2(char *line, int start, int end)
// {
// 	int	i;
// 	int	j;
// 	int	len;
// 	char	*new_line;

// 	i = 0;
// 	j = 0;
// 	len = 0;
// 	if (line != NULL)
// 		len = ft_strlen(line);
// 	new_line = malloc(sizeof (char) * len);
// 	if (!new_line)
// 		return (NULL);
// 	while (new_line[i])
// 	{
// 		new_line[i] = '\0';
// 		i++;
// 	}
// 	i = 0;
// 	while (line[i])
// 	{
// 		// if (i != start && line[i] != '\"' && line[i + 1] == '\'')
// 		// 	i += 2;
// 		// if (line[i] == '\'' && (i + 1) != end)
// 		// 	i += 2;
// 		if (i == start || i == end || line[i] == '\"')
// 		{
// 			i++;
// 			while (line[i] == '\"')
// 				i++;
// 		}
// 		new_line[j] = line[i];
// 		//printf ("char %c\n", new_line[j]);
// 		i++;
// 		j++;
// 	}
// 	i = 0;
// 	free(line);
// 	// while (line[i])
// 	// {
// 	// 	free(line[i]);
// 	// 	i++;
// 	// }
// 	//printf("# %s\n",new_line);
// 	return (new_line);
// }


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:48:51 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/18 15:50:57 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tab_command(t_lst *lst)
{
	int	i = 0;
	assign_token(lst);
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->token == 0)
		{
			i = 0;
			//printf("command %s\n", lst->command);
			//printf(" %d\n", lst->token);
			lst->split_command = assign_tab_command(lst->command, lst);
			// while (lst->split_command[i])
			// {
			// 	printf ("%s | ", lst->split_command[i]);
			// 	i++;
			// }
			//printf ("%s\n", lst->split_command[i]);
			// printf("\n");
		}
		lst = lst->next;
	}
}

/*compter le nb d'index qu'il va falloir pour le split /compte les argument de la commande*/
int	len_tab_command(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			//printf("%c\n", s[i]);
			count++;
			i = i - 1;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			//printf("%c\n", s[i]);
			count++;
			i = i - 1;
		}
		if (s[i] != '\"' && s[i] != '\'' && s[i] != ' ' && s[i] != '\t')
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t')
				i++;
			//printf("%c\n", s[i]);
			count++;
			i = i - 1;
		}
		i++;
	}
	return (count);
}

char **malloc_command_in_lst(char *s, char **split)
{
	int	i;
	int	size;

	i = 0;
	size = len_tab_command(s);
	split = malloc(sizeof(char *) * (len_tab_command(s) + 1)); // \0
	if (!split)
		return (NULL);
	while (i < size + 1)
	{
		split[i] = NULL; // pas \0 car tt est mis a null
		i++;
	}
	return (split);
}

char	*word_dup_in_split(char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char **assign_tab_command(char *s, t_lst *lst)
{
	int		i;
	int		index;
	int		start;
	int		end;
	char	**split;

	i = 0;
	start = 0;
	end = 0;
	index = 0;
	split = NULL;
	split = malloc_command_in_lst(lst->command, split);
	while (s[index])
	{
		if (s[index] == '\'')
		{
			start = index;
			index++;
			while (s[index] && s[index] != '\'')
				index++;
			index++;
			end = index;
			index = index - 1;
			split[i] = word_dup_in_split(s, start, end);
			i++;
		}
		if (s[index] == '\"')
		{
			start = index;
			index++;
			while (s[index] && s[index] != '\"')
				index++;
			index++;
			end = index;
			index = index - 1;
			split[i] = word_dup_in_split(s, start, end);
			i++;
		}
		if (s[index] != '\"' && s[index] != '\'' && s[index] != ' ' && s[index] != '\t')
		{
			start = index;
			while (s[index] && s[index] != ' ' && s[index] != '\t')
				index++;
			end = index;
			index = index - 1;
			split[i] = word_dup_in_split(s, start, end);
			i++;
		}
		index++;
	}
	split[i] = NULL;
	return (split);
}
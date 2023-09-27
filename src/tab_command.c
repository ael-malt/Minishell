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

<<<<<<< HEAD
// int	limiteur(char c)
// {
// 	if (c == '|' || c == '<' ||
// 		c == '>')
// 		return (1);
// 	return (0);
// }

// int len_since_limiteur(char *s)
// {
//     int i;

//     i = 0;
//     while (s[i])
//     {
//         if (limiteur(s[i]) == 1)
//         {
//             break;
//             return (i);
//         }
//         i++;
//     }
//     return (i);
// }

// t_tree    *get_tree(char *s)
// {
//     int i;
//     int j;
//     int operator;
//     char *temp;
//     t_tree	*node;

//     i = 0;
//     j = 0;
//     operator = len_since_limiteur(s);
//     temp = malloc(sizeof (char) * len_since_limiteur(s));
//     while (i < operator || s[i])
//         temp[j++] = s[i++];
//     strdup(temp); //parser la commande
//     node = malloc(sizeof(node));
// 	if (!node)
// 		return (NULL);
//     //if (operator == ft_strlen(s))
//     node->content = &s[operator];
//     node->left = strdup(temp); //parser la commande 
//     node->right = get_tree(&s[operator + count]);
// }

// int len_operator(char *s, int start)
// {
//     int i;
//     int count;

//     i = 0;
//     count = 0;
//     while (s[start] != '\0' || limiteur(s[start]) != 0)
//     {
//         start++;
//         count++;
//     }  
//     return (count);
// }
=======
int	limiteur(char c)
{
	if (c == '|' || c == '<' ||
		c == '>')
		return (1);
	return (0);
}

int len_since_limiteur(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (limiteur(s[i]) == 1)
        {
            break;
            return (i);
        }
        i++;
    }
    return (i);
}

t_tree    *get_tree(char *s)
{
    int i;
    int j;
    int operator;
    char *temp;
    t_tree	*node;

    i = 0;
    j = 0;
    operator = len_since_limiteur(s);
    temp = malloc(sizeof (char) * len_since_limiteur(s));
    while (i < operator || s[i])
        temp[j++] = s[i++];
    strdup(temp); //parser la commande
    node = malloc(sizeof(node));
	if (!node)
		return (NULL);
    //if (operator == ft_strlen(s))
    node->content = &s[operator];
    node->left = strdup(temp); //parser la commande 
    node->right = get_tree(&s[operator + count]);
}

int len_operator(char *s, int start)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[start] != '\0' || limiteur(s[start]) != 0)
    {
        start++;
        count++;
    }  
    return (count);
}
>>>>>>> refs/remotes/origin/lara_dev

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

<<<<<<< HEAD
// int word_count(char *s)
// {
// 	int	i;
// 	int	word;

// 	i = 0;
// 	word = 0;
// 	while(s[i] || limiteur(s[i]))
// 	{
// 		if (s[i] == ' ')
// 			i++;
// 		if (s[i] != ' ' )
// 			word++;
// 		while (s[i] && s[i] != ' ')
// 			i++;
// 	}
// 	return (word);
// }

// int	len_word_count(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] && s[i] != ' ')
// 		i++;
// 	return (i);
// }

// int	is_command_simple(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (limiteur(s[i]) == 1)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
=======
int word_count(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while(s[i] || limiteur(s[i]))
	{
		if (s[i] == ' ')
			i++;
		if (s[i] != ' ' )
			word++;
		while (s[i] && s[i] != ' ')
			i++;
	}
	return (word);
}

int	len_word_count(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

int	is_command_simple(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (limiteur(s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
>>>>>>> refs/remotes/origin/lara_dev

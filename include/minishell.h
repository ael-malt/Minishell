/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/27 15:34:34 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// enum operator
// {
// 	PIPE, // |
// 	DREDIRIN, //heredoc
// 	DREDIROUT, // ajout a la fin d'un file
// 	REDIRIN, // <
// 	REDIROUT, // >
// };
// https://learn.microsoft.com/fr-fr/cpp/c-language/union-declarations?view=msvc-170
// typedef struct s_type
// {
// 	s_type	operator;
// 	s_type	command;
// }	t_type

typedef struct s_tree
{
	char			*content;
	char	*str1;
	char	*str2;
	int		len_command;
	int		len_str1;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//------------------------------PARSING.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
//---------------------------------------------------------------------//

//----------------------------MAIN.C-----------------------------------//
char	**get_tab_env(char **envp);
t_tree	*create_node();
void	len_split_command(t_tree *tree);
void	split_command(t_tree *tree);
char	*ft_strndup(char *s, int start, int end);
void	is_operator_split(t_tree *tree);
int	len_operator(t_tree *tree);
//---------------------------------------------------------------------//

//------------------------------TREE.C------------------------------//

//---------------------------------------------------------------------//

//---------------------TAB_COMMANDE--------------------------------------//


//---------------------------------------------------------------------//

#endif

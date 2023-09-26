/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/26 08:52:39 by lazanett         ###   ########.fr       */
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

enum operator
{
	PIPE, // |
	DREDIRIN, //heredoc
	DREDIROUT, // ajout a la fin d'un file
	REDIRIN, // <
	REDIROUT, // >
};
// https://learn.microsoft.com/fr-fr/cpp/c-language/union-declarations?view=msvc-170
typedef struct s_type
{
	s_type	operator;
	s_type	command;
}	t_type

typedef struct s_tree
{
	char			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//------------------------------PARSING.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
//---------------------------------------------------------------------//

//----------------------------MAIN.C-----------------------------------//
char	**get_tab_env(char **envp);
//---------------------------------------------------------------------//

//------------------------------TREE.C------------------------------//
// t_tree	*create_symbol(char *content);
// t_tree *insert(t_tree *tree, char *content);
//---------------------------------------------------------------------//

//---------------------TAB_COMMANDE--------------------------------------//
int	limiteur(char c);
char	**get_str(char *s);
int	len_word_count(char *s);
int	word_count(char *s);


//---------------------------------------------------------------------//

//------------------------------TREE.C------------------------------//
t_tree	create(char *content);
t_tree *insert(t_tree *tree, char *content);
//---------------------------------------------------------------------//
#endif

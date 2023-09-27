/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/27 17:23:51 by lazanett         ###   ########.fr       */
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
// t_tree	*create_symbol(char *content);
// t_tree *insert(t_tree *tree, char *content);
//---------------------------------------------------------------------//

//---------------------TAB_COMMANDE--------------------------------------//
int	limiteur(char c);
char	**get_str(char *s);
int	len_word_count(char *s);
int	word_count(char *s);


t_tree	*create_node();
void	len_split_command(t_tree *tree);
void	split_command(t_tree *tree);
char	*ft_strndup(char *s, int start, int end);
void	is_operator_split(t_tree *tree);
int	len_operator(t_tree *tree);
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

//---------------------------------------------------------------------//

//---------------------TAB_COMMANDE--------------------------------------//


//---------------------------------------------------------------------//

#endif

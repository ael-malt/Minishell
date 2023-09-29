/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/29 17:41:25 by lazanett         ###   ########.fr       */
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

//------------------------------FIRST_CHECK.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
//-------------------------------------------------------------------------//

//-------------------------MAIN.C------------------------------------------//
char	**get_tab_env(char **envp);

//--------------------------TREE.C-----------------------------------------//
t_tree	*create_node();
void	split_command(t_tree *tree);
void	tree_branch(t_tree *tree);
void	len_split_command(t_tree *tree);
char	*ft_strndup(char *s, int start, int end);

//------------------------OPERATOR.C---------------------------------------//
int	len_redirection(t_tree *tree, char *s);
int	res_is_operator(t_tree *tree, char *s);
void	is_operator_split(t_tree *tree);
int	len_operator(t_tree *tree);
int	is_operator(char c);

//------------------------REDIR.C-----------------------------------------//
//void	len_redir(t_tree *tree);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 17:57:31 by lazanett         ###   ########.fr       */
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

typedef struct s_lst
{
	char	*content;
	char	*command;
	char	*rest;
	int		len_command_total;
	int		len_com;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_expand
{
	char	**tab; // tableau d'environnement
	char	*expand;
	char	*replace;
	char	*title;
	char	*new_command;
	char	**new_tab;
}	t_expand;

//------------------------------FIRST_CHECK.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
int	quote_expand(int end, char *s);
//-------------------------------------------------------------------------//

//-------------------------MAIN.C------------------------------------------//
void	get_tab_env(t_expand *ex, char **envp);

//--------------------------TREE.C-----------------------------------------//
t_lst	*create_node();
void	split_command(t_lst *lst);
void	tree_branch(t_lst *tlst);
void	len_split_command(t_lst *lst);
char	*ft_strndup(char *s, int start, int end);

//------------------------OPERATOR.C---------------------------------------//
int	len_redirection(t_lst *tree, char *s);
int	res_is_operator(t_lst *tree, char *s);
void	is_operator_split(t_lst *lst);
int	len_operator(t_lst *lst);
int	is_operator(char c);

//------------------------EXPAND.C-----------------------------------------//
char	*search_expand_in_line(t_expand *ex, char *line);
char	*get_str2(t_expand *ex, char *line, int i);
int		len_expand(char *line, int i);
int		ft_strcmp(char *s1, char *s2);
char	*get_title(t_expand *en, char *tab_str);

//------------------------SWITCH.C----------------------------------------//
void	get_replace(t_expand *ex);
char	*ft_strjoin_connect(t_expand *ex, char *start, char *end);
void	ft_free_expand(t_expand *ex, char *str1, char *str2);

//--------------------------UNSET.C--------------------------------------//
int		invalid_arg_unset(char *s);
void	cmp_unset(char **av, t_expand *ex);
void	search_arg_unset(char *av, t_expand *ex);
char	**new_tab(t_expand *ex, int index);
int		len_tab(char **tab);

#endif

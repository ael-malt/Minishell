/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/17 14:38:02 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <stddef.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
//si = 0 = commande ; si == 1 = operateur ; si == 2 = redirection
typedef struct s_lst
{
	char	*content;
	char	*command;
	char	*rest;
	int		len_command_total;
	int		len_com;
	int		token; 
	char	**split_command;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_expand
{
	char	**tab;
	char	*expand;
	char	*replace;
	char	*title;
	char	*new_command;
	char	**new_tab;
	int		flag;
	pid_t	pid;
	// char	*str1;
	// char	*str2;
	
}	t_expand;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

//-----------------------------FIRST_CHECK.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
void	search_quote_in_split(t_lst *lst);
char	*supp_quote(char *s);
// char *get_line_since_quote(char *line);
// char *ft_new_line1(char *line, int start, int end);
// char *ft_new_line2(char *line, int start, int end);

//-------------------------------------------------------------------------//

//--------------------------------MAIN.C----------------------------------//
// void	get_tab_env(t_expand *ex, char **envp);

//--------------------------LST.C-----------------------------------------//
t_lst	*create_node();
void	split_command(t_lst *lst);
void	tree_branch(t_lst *tlst);
void	len_split_command(t_lst *lst);
void	assign_token(t_lst *lst);

//------------------------OPERATOR.C---------------------------------------//
int	len_redirection(t_lst *tree, char *s);
int	res_is_operator(t_lst *tree, char *s);
void	is_operator_split(t_lst *lst);
int	len_operator(t_lst *lst);
int	is_operator(char c);

//--------------------------------ENV.C--------------------------------//
char	*search_expand_in_line(t_expand *ex, char *line);
char 	*get_split_expand(char *str1, char *str2, t_expand *ex, char *line, int i);
char	*get_str2(t_expand *ex, char *line, int i);
int		len_expand(char *line, int i);
int		ft_strcmp(char *s1, char *s2);

//---------------------------------SWITCH.C-------------------------------//
char	*get_title(t_expand *en, char *tab_str);
void	get_replace(t_expand *ex);
char	*ft_strjoin_connect(t_expand *ex, char *start, char *end);
char	*ft_strndup(char *s, int start, int end);
void	ft_free_expand(t_expand *ex, char *str1, char *str2);

//---------------------------------BUILTINS.C-----------------------------//
int		builtin(char *cmd, t_expand	*ex);
int		mini_pwd(void);
int		mini_echo(t_list *cmd);
int mini_export(t_expand *ex, char *cmd);

//-----------------------------------UTIL.C-------------------------------//

int		ft_countchar(char *s, char c);

//-----------------------------------SIGNAL.C-----------------------------//
void	handle_sigint(int signal);

//-----------------------------------ERROR.C-----------------------------//
void	*mini_perror(int err_type, char *param, int err);
//--------------------------UNSET.C--------------------------------------//
int		invalid_arg_unset(char *s);
void	cmp_unset(char **av, t_expand *ex);
void	search_arg_unset(char *av, t_expand *ex);
char	**new_tab(t_expand *ex, int index);
int		len_tab(char **tab);

//------------------------LST_SPLIT-------------------------------------//
void	tab_command(t_lst *lst);
int		len_tab_command(char *s);
char	**malloc_command_in_lst(char *s, char **split);
char	*word_dup_in_split(char *str, int start, int finish);
char	**assign_tab_command(char *s, t_lst *lst);


void dump(t_lst *node);

#endif

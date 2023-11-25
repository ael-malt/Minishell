/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/25 15:28:43 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include "colors.h"
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <stddef.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
/*
TO-DO

* verif $? message erreur ==> lara aider par Amine
* echo $? ne reset pas le return code ==> lara
* verif error si trop operator ==> lara

* etendre redir au multi-pipe
* etendre here doc au redir en general ==> Amine

*/
typedef struct s_lst
{
	struct	s_expand	*ex;
	char	*content;
	char	*command;
	char	*rest;
	int		len_command_total;
	int		len_com;
	int		token;
	char	**split_command;
	char	**split_redir;
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
	char	*str1;
	char	*str2;
	int		flag;
	int		i;
	int		c;
	int		j;
	int		count;
	size_t	k;
	size_t	l;
	size_t	m;
	pid_t	pid;

}	t_expand;

typedef	struct s_split
{
	char	**split;
	int		start;
	int		end;
	int		index;
	int		i;
	int		flag;
	char	**strs;
	int		j;
	int		k;
}	t_split;


enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	PIPENDERR = 8,
	MEM = 9,
	IS_DIR = 10,
	NOT_DIR = 11,
	OPERROR = 12,
	NOTCMD = 13,
	NONAME = 14,
	SYNTAX = 15,
	NOQUOTE = 16
};

//--------------------------------MAIN.C----------------------------------//
// void	get_tab_env(t_expand *ex, char **envp);
void	check_rl_args(char *line, t_lst *lst, t_expand *ex, t_split *sp);
void	start_execution(t_lst *lst,t_expand *ex);
//----------------------------0_FIRST_CHECK.C------------------------------//
int		search_char(char *s);
int		search_quote(char *s);
int		check_double_pipe(t_lst *lst);
int		check_last_is_pipe(t_lst *lst);

//--------------------------1_LST.C-----------------------------------------//
t_lst	*create_node();
void	strndup_operator(t_lst *lst); // nouveau
int		split_command(t_lst *lst, t_expand *ex);
int		tree_branch(t_lst *lst, t_expand  *ex);
void	len_split_command(t_lst *lst);


//------------------------2_OPERATOR.C---------------------------------------//
int		is_operator_split(t_lst *lst);
int		len_operator(t_lst *lst);
int		error_operator_return(int i, char *s);
void	error_operator_message(char *s);

//------------------------3_OPERATOR_UTILS.C---------------------------------//
void	assign_token(t_lst *lst);
int		is_operator(char c);
int		res_is_operator(t_lst *tree, char *s);
int		len_redirection(t_lst *tree, char *s);

//-------------------------4_EXPAND.C--------------------------------//
void	expand_lst(t_lst *lst, t_expand *ex);
char	*search_expand_in_line(t_expand *ex, char *line, int i);
char 	*get_split_expand(t_expand *ex, char *line, int i);
char	*get_str2(t_expand *ex, char *line, int i);

//------------------------5_SWITCH.C-------------------------------//
char	*get_title(t_expand *en, char *tab_str);
void	get_replace(t_expand *ex);
void	assign_replace(t_expand *ex);

//----------------------6_EXPAND_UTILS.C---------------------------//
char	*ft_strjoin_connect(t_expand *ex, char *start, char *end);
void	get_len_strjoin_connect(t_expand *ex, char *start, char *end);
char	*ft_strndup(char *s, int start, int end);
int		len_expand(char *line, int i);
int		ft_strcmp(char *s1, char *s2);

//------------------------7_LST_LEN_SPLIT.C-------------------------------------//
void	tab_command(t_lst *lst, t_split *sp);
int		len_tab_command(char *s); // nouveau ajout i
int		search_next_word(char *s, int i); // nouveau
int 	search_next_word_simple_quote(char *s, int i);
int 	search_next_word_double_quote(char *s, int i);

//------------------------8_LST_SPLIT.C---------------------------------------//
char	**malloc_command_in_lst(char *s, char **split);
char	*word_dup_in_split(char *str, int start, int finish);
char	**assign_tab_command(char *s, t_lst *lst, t_split *sp);
void	get_word_limit(char *s,  t_split *sp);
void	get_limit_word_quote(char *s, t_split *sp);

//------------------------9_SPLIT_REDIR.C-------------------------------------//
char	**ft_split_redir(char *str, char *charset, t_split *s);
void	operator_split_redir(char *str, char *charset, t_split *s);
void	word_split_redir(char *str, char *charset, t_split *s);

//----------------------10_SPLIT_REDIR_UTILS.C-------------------------------//
int		check_charset(char c, char *charset);
int		count_words(char *str, char *charset);
int		count_wlen(char *str, char *charset);

//------------------------11_SUPP_QUOTTE.C--------------------------//
void	search_quote_in_split_command(t_lst *lst);
void	search_quote_in_split_redir(t_lst *lst);
char	*supp_quote(char *s, int len, int index, int flag);

//------------------------12_SUPP_QUOTTE_UTILS.C--------------------------//
int		is_quote(char *s);
char	*malloc_char_supp_quotte(int len, char *rep, char *s);
int		check_is_name_for_redir(t_lst *lst);

//-----------------------------------UTIL.C-------------------------------//
int		ft_countchar(char *s, char c);
void	print_big_minishell();
char	*get_line_info(t_expand *ex);

//-----------------------------------SIGNAL.C-----------------------------//
void	handle_sigint(int signal);

//-----------------------------------ERROR.C-----------------------------//
void	*mini_perror(int err_type, char *param, int err);
int		mini_export_error(char *cmd);
void	*mini_perror2(int err_type, char param, int err);
void	free_lst(t_lst *lst);
void	ft_free_expand(t_expand *ex);
void	clean_return(t_lst *lst, t_expand *ex);
void	*mini_perror_exec(int err_type, char **split_command);
void	*mini_heardoc_error(int err_type, char *param, int err);

//-------------------------------BUILTINS------------------------------//

int		builtin(t_lst *lst, t_expand	*ex);
int		is_builtin(t_lst *lst);

		//--------------------------CD.C----------------------------//
int		mini_cd(t_expand *ex, char **split_command);

		//-------------------------ECHO.C---------------------------//
int		mini_echo(t_lst *lst);

		//-------------------------EXIT.C--------------------------//
int		mini_exit(char **split_command);

		//------------------------EXPORT.C--------------------------//
int		export_var_in_tab(char *cmd, char **tab);
int		mini_export(t_expand *ex, char **split_command);

		//--------------------------PWD.C---------------------------//
int		mini_pwd(void);

		//-------------------------UNSET.C--------------------------//
int		unset_var_in_tab(char *av, char **tab);
int		mini_unset(t_expand *ex, char **av);
char	**new_tab(t_expand *ex, int index);

//---------------------------------EXECUTION------------------------------//

		//-----------------EXECUTION_UTIL.C---------------------------//
int		lst_count_pipe(t_lst *lst);
int		get_last_operator(t_lst *lst);
int		len_lst(t_lst *lst);

		//----------------------EXECUTION.C----------------------------//
void	execute(t_lst *lst, t_expand *ex);
void	excecuting(t_lst *lst, char **tab);
char	*ft_strjoin_connect2(char const *s1, char const *s2, char connector);
void	exc_absolut_way(t_lst *lst, t_expand *ex);
int		is_builtin(t_lst *lst);

		//-------------------------HEREDOC.C------------------------//
int		is_heredoc(t_lst *lst);
void	mini_heredoc(t_lst *lst);
int		is_heredoc_limiter_valid(t_lst *lst);
void	heredoc_signal(int fd, int i);

		//---------------------MULTI_PIPE.C----------------------------//
int		multi_pipe(t_lst * lst, t_expand *ex);
void	redirex(int file, t_lst *lst);
void	pipex(int *fd, int *fd_temp, t_lst *lst);

		//------------------------REDIR_UTIL.C----------------------//
int		is_redir(t_lst *lst);
int		open_redir_file(t_lst *lst);
void	redirect(t_lst *lst);
int		is_solo_redir(t_lst *lst);
int		lst_count_redir(t_lst *lst);

#endif

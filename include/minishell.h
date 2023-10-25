/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/25 15:44:37 by lazanett         ###   ########.fr       */
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
//si = 0 = commande ; si == 1 = operateur ; si == 2 = redirection
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

}	t_expand;

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
	NOTCMD = 13
};

int multipipe(t_lst * lst, t_expand *ex);
//-----------------------------FIRST_CHECK.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
void	search_quote_in_split(t_lst *lst);
char	*supp_quote(char *s, int len, int index);
// char *get_line_since_quote(char *line);
// char *ft_new_line1(char *line, int start, int end);
// char *ft_new_line2(char *line, int start, int end);

//-------------------------------------------------------------------------//

//--------------------------------MAIN.C----------------------------------//
// void	get_tab_env(t_expand *ex, char **envp);

//--------------------------LST.C-----------------------------------------//
t_lst	*create_node();
int	split_command(t_lst *lst, t_expand *ex);
int	tree_branch(t_lst *lst, t_expand  *ex);
void	len_split_command(t_lst *lst);
void	assign_token(t_lst *lst);

//------------------------OPERATOR.C---------------------------------------//
int	len_redirection(t_lst *tree, char *s);
int	res_is_operator(t_lst *tree, char *s);
int	is_operator_split(t_lst *lst);
int	len_operator(t_lst *lst);
int	error_operator_return(int i, char *s);
void	error_operator_message(char *s);
int	is_operator(char c);

//--------------------------------EXPAND.C--------------------------------//
void	expand_lst(t_lst *lst, t_expand *ex);
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
//------------------------LST_SPLIT-------------------------------------//
int	is_heredoc(t_lst *lst);
int	mini_heredoc(t_lst *lst);

//------------------------LST_SPLIT-------------------------------------//
void	tab_command(t_lst *lst);
int		len_tab_command(char *s);
char	**malloc_command_in_lst(char *s, char **split);
char	*word_dup_in_split(char *str, int start, int finish);
char	**assign_tab_command(char *s, t_lst *lst);

//-------------------------GET_COMMAND----------------------------------//
int		is_solo_ex(t_lst *lst);
void	solo_exe(t_lst *lst, t_expand *ex);
void	excecuting(t_lst *lst, char **tab);
char	*ft_strjoin_connect2(char const *s1, char const *s2, char connector);
void	exc_absolut_way(t_lst *lst);
int		is_builtin(t_lst *lst);
//----------------------MULTI_PIPE.C-----------------------------------//
int		lst_count_pipe(t_lst *lst);
int		len_lst(t_lst *lst);
void	multi_pipe(t_lst * lst, t_expand *ex);
void	pipex(int *fd, int *fd_temp, t_lst *lst, t_expand *ex);
void	exc_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex);
void	last_pipe(int *fd, int *fd_temp, t_lst *lst,t_expand *ex);
void	exc_last_cmd(int *fd, int fd_temp, t_lst *lst, t_expand *ex);

//---------------------------------BUILTINS.C-----------------------------//

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
int		len_tab(char **tab);

#endif

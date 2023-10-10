/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 12:33:29 by ael-malt         ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//-----------------------------STRUCTURES------------------------------//

typedef struct s_prompt
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}			t_prompt;

typedef struct s_mini
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_mini;

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

typedef struct s_expand
{
	char	**tab; // tableau d'environnement
	char	*expand;
	char	*replace;
	char	*title;
	char	*new_command;
	// char	*str1;
	// char	*str2;
	
}	t_expand;

//------------------------------FIRST_CHECK.C------------------------------//
int	search_char(char *s);
int	search_quote(char *s);
int	quote_expand(int end, char *s);
//-------------------------------------------------------------------------//

//---------------------------------------------------------------------//
char	**get_tab_env(char **envp);

//------------------------------BUILTINS.C-----------------------------//
int		mini_pwd(void);
int	mini_echo(t_list *cmd);

//--------------------------------UTIL.C-------------------------------//

int	ft_countchar(char *s, char c);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:10:09 by lazanett          #+#    #+#             */
/*   Updated: 2023/09/21 16:49:22 by lazanett         ###   ########.fr       */
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
	int				content;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

//------------------------------PARSING.C------------------------------//
//int	ft_strrchr_(const char *s, char c);
int	search_char(char *s);
int	search_quote(char *s);
int	limiteur(char *s);

//---------------------------------------------------------------------//
char	**get_tab_env(char **envp);

#endif

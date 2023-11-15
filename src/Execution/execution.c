/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:56:53 by ael-malt          #+#    #+#             */
/*   Updated: 2023/11/15 17:05:55 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	start_execution(t_lst *lst,t_expand *ex)
{
	int	file;

	if (is_solo_redir(lst) == 0 && !lst_count_pipe(lst))
		solo_exe(lst, ex); // av 0 changer a 1 pour 1 redir
	else if(is_solo_redir(lst) == 1 && !lst_count_pipe(lst)
		&& ((is_redir(lst) == 2 || is_redir(lst) == 4
		|| (is_redir(lst->next) == 2 || is_redir(lst->next) == 4))))
		{
			file = open_redir_file(lst);
			if (is_redir(lst))
				solo_redir_out(lst, ex, file);
			else if (is_redir(lst->next))
				solo_redir_out(lst, ex, file);
		}
	else if(is_solo_redir(lst) == 1 && (is_redir(lst) == 3 || (lst->next && is_redir(lst->next) == 3)) && !lst_count_pipe(lst))
		{
			file = open_redir_file(lst);
			solo_redir_in(lst, ex, file);
		}
	else if (is_solo_redir(lst) == 1 && is_redir(lst) == 1 && !lst_count_pipe(lst))
		mini_heredoc(lst);
	else
		multi_pipe(lst, ex);
	if (file)
		close(file);
}

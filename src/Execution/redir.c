/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:07:53 by lazanett          #+#    #+#             */
/*   Updated: 2023/11/15 15:50:31 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exit_status;

// void	exc_cmd2(int *fd, int *fd_temp, t_lst *lst, t_expand *ex)
// {
// 	int	outfile;

// 	outfile = open(lst->next->split_redir[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (outfile < 0)
// 	{
// 		close(fd[1]);
// 		close(fd[0]);
// 		ft_perror("Outfile");
// 	}	
// 	if (dup2(fd_temp, STDIN_FILENO) == -1)
// 		ft_perror("Dup");
// 	if (dup2(outfile, STDOUT_FILENO) == -1)
// 		ft_perror("Dup");
// 	close(fd[1]);
// 	close(fd[0]);
// 	close(outfile);
// 	close(fd_temp);
// 	if (is_builtin(lst) == 1)
// 		builtin(lst, ex);
// 	if (ft_strchr(lst->split_command[0], '/') != NULL)
// 		exc_absolut_way(lst);
// 	else
// 		excecuting(lst, ex->tab);
// }

// void	open_file(t_lst *lst)
// {
// 	if (is_redir(lst) <= 0)
// 		return ;
// 	else
// 	{
// 		if (is_redir(lst) == 4)
// 			open(,O_WRONLY | O_CREAT | O_APPEND, 0644); // mettre fd necessaire
// 		if (is_redir(lst) == 3)
// 			open(, O_RDONLY, 0644);
// 		if (is_redir(lst) == 2)
// 			open (,O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (is_redir(lst) == 1)
// 			open(O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	}
// }

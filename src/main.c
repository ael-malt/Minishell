/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/14 16:14:49 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;
/*geger les erreur de variable globale check 2pipe = 2 : command not found*/
static void	mini_getpid(t_expand *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->tab);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->tab);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

void	start_execution(t_lst *lst,t_expand *ex)
{
	if (is_solo_redir(lst) == 0 && !lst_count_pipe(lst))
		solo_exe(lst, ex); // av 0 changer a 1 pour 1 redir
	else if(is_solo_redir(lst) == 1 && !lst_count_pipe(lst)
		&& ((is_redir(lst) == 2 || is_redir(lst) == 4
		|| (is_redir(lst->next) == 2 || is_redir(lst->next) == 4))))
		{
		if (is_redir(lst))
			solo_redir_out(lst, ex, is_redir(lst));
		else if (is_redir(lst->next))
			solo_redir_out(lst, ex, is_redir(lst->next));
		}
	else if(is_solo_redir(lst) == 1 && (is_redir(lst) == 3 || (lst->next && is_redir(lst->next) == 3)) && !lst_count_pipe(lst))
		solo_redir_in(lst, ex);
	else if (is_solo_redir(lst) == 1 && is_redir(lst) == 1 && !lst_count_pipe(lst))
		mini_heredoc(lst);
	else
		multi_pipe(lst, ex);
}

void	check_rl_args(char *line, t_lst *lst, t_expand *ex, t_split *sp)
{
	if (line[0])
		add_history(line);
	while (line[0] == ' ' || (line[0] >= '\a' && line[0] <= '\r'))
		line++;
	if (line[0])
	{
		//new_line = search_expand_in_line(&ex, line);
		//printf("%s\n", new_line);
		lst = create_node();
		lst->content = ft_strdup(line);
		if (split_command(lst, ex) != -1)
		{
			assign_token(lst);
			expand_lst(lst, ex);
			tab_command(lst, sp);
			search_quote_in_split_command(lst);
			search_quote_in_split_redir(lst);
			if (check_double_pipe(lst) == 0 && check_is_name_for_redir(lst) == 0)
				start_execution(lst, ex);
		}
		else
			clean_return(lst, ex);
	}
}

void	export_envp(t_expand *ex, char **envp)
{
	char	*pwd;
	char	*tmp;
	
	if (envp[0] != NULL)
		ex->tab = ft_dup_matrix(envp);
	else
	{
		ex->tab = malloc(sizeof(ex->tab) * 4);
		if (!ex->tab)
			return ;
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		ex->tab[0] = ft_strdup(pwd);
		free(pwd);
		ex->tab[1] = ft_strdup("SHLVL=1");
		ex->tab[2] = ft_strdup("_=/usr/bin/env");
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)		av;
	t_expand	ex;
	t_lst		lst;
	t_split		sp;
	char		*line_start;
	char		*line;

	if (ac == 1)
	{
		export_envp(&ex, envp);
		mini_getpid(&ex);
		print_big_minishell();
		while (1)
		{
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
			line_start = get_line_info(&ex);
			line = readline(line_start);
			if (!line)
				break ;
			else
				check_rl_args(line, &lst, &ex, &sp);
			// free line
			free(line_start);
		}
		// if (lst.content)
		// 	free_lst(&lst);
		ft_printf("exit\n");
		exit(g_exit_status);
	}
	else
		printf("Error : nb argc invalid\n");
}

// void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
// {
// 	int	size;
// 	int	i;
	
// 	size = 0;
// 	while (envp[size])
// 		size++;
// 	ex->tab = malloc (sizeof(char *) * (size + 1));
// 	if (!ex->tab)
// 		return ;
// 	i = 0;
// 	while (i < size + 1)
// 	{
// 		ex->tab[i] = NULL;
// 		i++;
// 	}
// 	i = 0;
// 	while (envp[i])
// 	{
// 		ex->tab[i] = ft_strdup(envp[i]);
// 		if (ex->tab[i] == 0)
// 		{
// 			free(ex->tab[i]);
// 			exit(1);
// 		}
// 		// printf("%s\n", ex->tab[i]);
// 		i++;
// 	}
// 	return;
// }


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/11/23 16:30:10 by ael-malt         ###   ########.fr       */
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

void	check_rl_args(char *line, t_lst *lst, t_expand *ex, t_split *sp)
{
	if (line[0])
		add_history(line);
	while (line[0] == ' ' || (line[0] >= '\a' && line[0] <= '\r'))
		line++;
	if (line[0])
	{
		if (search_quote(line) == 1)
		{
			mini_perror(QUOTE, "", 2);
			return ;
		}
		if (search_char(line) == 1)
		{
			mini_perror2(OPERROR, ' ', 2);// a voir ce quon met en code err
			return ;
		}
		lst = create_node();
		lst->content = ft_strdup(line);
		if (split_command(lst, ex) != -1)
		{
			assign_token(lst);
			expand_lst(lst, ex);
			tab_command(lst, sp);
			search_quote_in_split_command(lst);
			search_quote_in_split_redir(lst);
			if (check_double_pipe(lst) == 0 && check_last_is_pipe(lst) == 0)
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
			// printf("line: %s\n", line);
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

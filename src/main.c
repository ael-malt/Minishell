/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/23 02:10:59 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

/*
	TO DO =
	recuperation du path (pipex) mais avec mon ex->tab (env local)
	lancer une commande fork et exceve
*/

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

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_lst	*lst;
	t_expand	ex;
	char	*line_start;
	char	*line;
	if (ac == 1)
	{
		ex.tab = ft_dup_matrix(envp);
		mini_getpid(&ex);
		print_big_minishell();
		while (1)
		{
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
			line_start = get_line_info(&ex);
			line = readline(line_start);
			if (line)
			{
				add_history(line);
				//new_line = search_expand_in_line(&ex, line);
				//printf("%s\n", new_line);
				lst = create_node();
				lst->content = ft_strdup(line);
				if (split_command(lst, &ex) != -1)
				{
					expand_lst(lst, &ex);
					tab_command(lst);
					search_quote_in_split(lst);
					builtin(lst, &ex);
					// pipex(lst, &ex);
				}
				else
					clean_return(lst, &ex);
			}
			// free line
			free(line_start);
		}
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


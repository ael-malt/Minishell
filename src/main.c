/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/10/17 18:14:44 by ael-malt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_exit_status;

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

void	print_big_minishell()
{
	ft_printf("\x1b[31mMMM      MMM   IIIIIIIIIIII  NNNNN    NNN  IIIIIIIIIIII \
 SSSSSSSSSSSS  HHH      HHH  EEEEEEEEEEEE  LLL           LLL         \n");
	ft_printf("\x1b[33mM|\\MM  MM/|M   IIII\\II/IIII  N|¯\\NN   N|N  IIII\\II/IIII \
 SS/¯SSSSSSSS  H|H      H|H  EE/EEEEEEEEE  L|L           L|L         \n");
	ft_printf("\x1b[32mM|M\\MMMM/M|M       I||I      N|NN\\N   N|N      I||I     \
 S¦SS          H|H      H|H  E|E           L|L           L|L         \n");
	ft_printf("\x1b[32mM|MM\\/\\/MM|M       I||I      N|N N\\N  N|N      I||I     \
 SS\\SSSSSSSSS  H|HHHHHHHH|H  E¦\\EEEEEEE    L|L           L|L         \n");
	ft_printf("\x1b[36mM|M      M|M       I||I      N|N  N\\N N|N      I||I     \
 SSSSSSSS\\SSS  H|HHHHHHHH|H  E¦/EEEEEEE    L|L           L|L         \n");
	ft_printf("\x1b[36mM|M      M|M       I||I      N|N   N\\NN|N      I||I     \
         S¦SS  H|H      H|H  E|E           L|L           L|L         \n");
	ft_printf("\x1b[34mM|M      M|M   IIII/II\\IIII  N|N    N\\_/N  IIII/II\\IIII \
 SSSSSSSS_/SS  H|H      H|H  EE\\EEEEEEEEE  L\\_LLLLLLLLL  L\\_LLLLLLLLL\n");
	ft_printf("\x1b[35mMMM      MMM   IIIIIIIIIIII  NNN     NNNN  IIIIIIIIIIII \
 SSSSSSSSSSSS  HHH      HHH  EEEEEEEEEEEE  LLLLLLLLLLLL  LLLLLLLLLLLL\n\x1b[0m");
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_lst	*lst;
	//t_lst *tmp;
	t_expand	ex;
	char	*line;
	char	*new_line;
	if (ac == 1)
	{
		//get_tab_env(envp);
		// while (envp[bleu])
		// 	printf("%s\n", envp[bleu++]);
		// get_tab_env(&ex, envp);
		ex.tab = ft_dup_matrix(envp);
		mini_getpid(&ex);
		ft_printf("\033[2J\033[1;1H");
		print_big_minishell();
		while (1)
		{
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, SIG_IGN);
			line = readline("=======> Minishell: ");
			if (line)
			{
				add_history(line);
				new_line = search_expand_in_line(&ex, line);
				printf("%s\n", new_line);
				lst = create_node();
				lst->content = ft_strdup(new_line);
				split_command(lst);
				tab_command(lst);
				search_quote_in_split(lst);

				//dump(lst);
				// new_line = get_line_since_quote(new_line);
				// printf("%s\n", new_line);
				//===>nouvelle fonction
				// tmp = lst;
				// while (tmp)
				// {
				// 	printf("command : %s\n", tmp->command);
				// 	tmp = tmp->next;
				// }
				
				builtin(line, &ex);
				// if (search_char(line) == 1 || search_quote(line) == 1)
				// 	printf("Error : line invalid \n");

			}
			// free line
		}
		exit(g_exit_status);
	}
	else
		printf("Error : nb argc invalid\n");
}

void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
{
	int	size;
	int	i;
	
	size = 0;
	while (envp[size])
		size++;
	ex->tab = malloc (sizeof(char *) * (size + 1));
	if (!ex->tab)
		return ;
	i = 0;
	while (i < size + 1)
	{
		ex->tab[i] = NULL;
		i++;
	}
	i = 0;
	while (envp[i])
	{
		ex->tab[i] = ft_strdup(envp[i]);
		if (ex->tab[i] == 0)
		{
			free(ex->tab[i]);
			exit(1);
		}
		// printf("%s\n", ex->tab[i]);
		i++;
	}
	return;
}


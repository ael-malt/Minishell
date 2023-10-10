/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 15:39:56 by ael-malt         ###   ########.fr       */
=======
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:12:04 by lazanett          #+#    #+#             */
/*   Updated: 2023/10/10 15:25:56 by lazanett         ###   ########.fr       */
>>>>>>> main
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

int	main(int ac, char **av, char **envp)
{
	(void) av;
	t_tree	*tree;
	t_expand	ex;
	char	*line;
	char	*coucou;
	if (ac == 1)
	{
<<<<<<< HEAD
		//get_tab_env(envp);
		// while (envp[bleu])
		// 	printf("%s\n", envp[bleu++]);
		// get_tab_env(&ex, envp);
		ex.tab = ft_dup_matrix(envp);
		mini_getpid(&ex);

=======
		get_tab_env(&ex, envp);
>>>>>>> main
		while (1)
		{
			signal(SIGINT, handle_sigint);
			// signal(SIGQUIT, SIG_IGN);
			line = readline("Minishell: ");
			if (line)
			{
				add_history(line);
				coucou = search_expand_in_line(&ex, line);
<<<<<<< HEAD
				// printf("%s\n", coucou);
				builtin(line);
				// if (search_char(line) == 1 || search_quote(line) == 1)
				// 	printf("Error : line invalid \n");


=======
				printf("%s\n", coucou);
				tree = create_node();
				tree->content = ft_strdup(coucou);
				//printf("%s\n", tree->content);
				split_command(tree);
>>>>>>> main
			}
			// free line
		}
		exit(g_exit_status);
	}
	else
		printf("Error : nb argc invalid\n");
}

<<<<<<< HEAD
// int	main(int ac, char **av, char **envp)
// {
// 	//t_tree	*tree;
// 	t_expand	ex;
// 	if (ac == 2)
// 	{
// 		get_tab_env(&ex, envp);
// 		printf("%s\n", search_expand_in_line(&ex, av[1]));
// 		// tree = create_node();
// 		// tree->content = ft_strdup(av[1]);
// 		// printf("%s\n", tree->content);
// 		// split_command(tree);
// 	}
// }

// void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
// {
// 	int	size;

// 	size = 0;
// 	while (envp[size])
// 		size++;
// 	ex->tab = malloc (sizeof(char *) * (size + 1));
// 	if (!ex->tab)
// 		return ;
// 	int i = 0;
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

// char	**get_str(char *s) //commande a mettre dans un maillon; si nv commande aller vers la droite
// {
// 	int	i;
// 	int j;
// 	int k;
// 	char **tab;
// 	char *temp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	tab = malloc(sizeof(char *) * word_count(s));
// 	while (limiteur(s[i]) != 1 || s[i])
// 	{
// 		if (s[i] && s[i] == ' ')
// 			i++;
// 		if (limiteur(s[i]) != 1 && s[i] && s[i] != ' ')
// 		{
// 			temp = malloc(sizeof (char) * len_word_count(&s[i]));
// 			while (s[i] && s[i] != ' ')
// 			{
// 				temp[k] = s[i];
// 				i++;
// 				k++;
// 			}
// 			tab[j] = strdup(temp);
// 			printf("%s\n", tab[j]);
// 			//printf("%c\n", s[i]);
// 			j++;
// 			k = 0;
// 			free(temp);
// 			//temp = NULL;
// 		}
// 		if (limiteur(s[i]) == 1)
// 		{
// 			break;
// 			return (tab);
// 		}	
// 		if (s[i] == '\0')
// 			return (tab);
// 	}
// 	return (tab);
// }
=======
void	get_tab_env(t_expand *ex, char **envp) // recup l'environnement
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	ex->tab = malloc (sizeof(char *) * (size + 1));
	if (!ex->tab)
		return ;
	int i = 0;
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
>>>>>>> main

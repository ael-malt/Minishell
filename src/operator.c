#include "../include/minishell.h"

void	is_operator_split(t_tree *tree)
{
	int	i;

	i = 0;
	tree->str1 = malloc(sizeof (char) * (len_operator(tree) + 1));
	while (tree->content[i] && is_operator(tree->content[i]) == 1)
	{
		tree->str1[i] = tree->content[i];
		i++;
	}
	tree->str1[i] = '\0';
	while (tree->content[i] == ' ' || tree->content[i] == '\t')
		i++;
	tree->str2 = ft_strndup(tree->content, i, (tree->len_command - 1));
}

int	len_redirection(t_tree *tree, char *s)
{
	int	i;

	i = 0;
	if (is_operator(tree->content[0]) == 1)
		i = len_operator(tree);
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] != '\0' && (s[i] != ' ' && s[i] != '\t' && is_operator(s[i]) == 0))
		i++;
	return (i);
}

int	len_operator(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->content[i] && is_operator(tree->content[i]) == 1)
	{
		if (i > 0 && (tree->content[i - 1] != tree->content[i]))
		{
			printf("Error : operator diff\n");
			exit(0);
		}
		i++;
	}
	if (tree->content[0] == '|' && i > 1)
	{
		printf("Error : multi pipe\n");
		exit(0);
	}
	if (i > 2)
	{
		printf("Error : trop d'operateur\n");
		exit(0);
	}
	else
		return (i);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	res_is_operator(t_tree *tree, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_operator(s[i]))
			count++;
		i++;
	}
	if (tree->len_command == count)
	{
		printf("Error : rest just operator\n"); // exit ??
		return (1);
	}
	return (0);
}
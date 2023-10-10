#include "../include/minishell.h"

void	is_operator_split(t_lst *lst)
{
	int	i;

	i = 0;
	lst->command = malloc(sizeof (char) * (len_operator(lst) + 1));
	while (lst->content[i] && is_operator(lst->content[i]) == 1)
	{
		lst->command[i] = lst->content[i];
		i++;
	}
	lst->command[i] = '\0';
	while (lst->content[i] == ' ' || lst->content[i] == '\t')
		i++;
	lst->rest = ft_strndup(lst->content, i, (lst->len_command_total - 1));
}

int	len_redirection(t_lst *lst, char *s)
{
	int	i;

	i = 0;
	if (is_operator(lst->content[0]) == 1)
		i = len_operator(lst);
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] != '\0' && (s[i] != ' ' && s[i] != '\t' && is_operator(s[i]) == 0))
		i++;
	return (i);
}

int	len_operator(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst->content[i] && is_operator(lst->content[i]) == 1)
	{
		if (i > 0 && (lst->content[i - 1] != lst->content[i]))
		{
			printf("Error : operator diff\n");
			exit(0);
		}
		i++;
	}
	if (lst->content[0] == '|' && i > 1)
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

int	res_is_operator(t_lst *lst, char *s)
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
	if (lst->len_command_total == count)
	{
		printf("Error : rest just operator\n"); // exit ??
		return (1);
	}
	return (0);
}
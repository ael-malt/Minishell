#include "../include/minishell.h"

int	is_operator_split(t_lst *lst)
{
	int	i;

	i = 0;
	if (len_operator(lst) == -1)
		return (-1);
	lst->command = malloc(sizeof (char) * (len_operator(lst) + 1));
	if (!lst->command)
		return (-1);
	while (lst->content[i] && is_operator(lst->content[i]) == 1)
	{
		lst->command[i] = lst->content[i];
		i++;
	}
	lst->command[i] = '\0';
	while (lst->content[i] == ' ' || lst->content[i] == '\t')
		i++;
	lst->rest = ft_strndup(lst->content, i, (lst->len_command_total - 1));
	return (0);
}

int	len_redirection(t_lst *lst, char *s)
{
	int	i;

	i = 0;
	if (is_operator(lst->content[0]) == 1)
	{
		i = len_operator(lst);
		if (i == -1)
			return (-1);
	}
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
		i++;
	if (!error_operator_return(i, lst->content))
		return (i);
	else
		return (-1);
}
	
int	error_operator_return(int i, char *s)
{
	if (s[0] == '|' && i > 1)
		return (1);
	else if (i > 2 && s[0] == s[1])
		return (1);
	return (0);
}

void	error_operator_message(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_operator(s[i]) == 1)
		i++;
	if (s[0] == '|' && i > 1)
		mini_perror2(OPERROR, s[1], 2);
	else if (i > 2 && s[0] == s[1])
		mini_perror2(OPERROR, s[2], 2);
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
		return (1);
	return (0);
}
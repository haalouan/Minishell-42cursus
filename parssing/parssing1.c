/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/06 09:21:40 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_tab(char *line, char **tab, int len)
{
	int	i;

	i = 0;
	if (!tab)
		exit(EXIT_FAILURE);
	while (tab[i] != NULL)
		i++;
	tab[i] = malloc(len + 1);
	if (!tab[i])
		exit(EXIT_FAILURE);
	ft_strncpy(tab[i], line, len);
}

char	**handle_parssing(char *line, t_env *env_list)
{
	int		count;
	t_check	check;
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	count = count_cmds(line);
	tab = malloc(sizeof(char *) * (count + 1) + 1);
	if (!tab)
		exit(EXIT_FAILURE);
	while (i <= count)
	{
		tab[i] = NULL;
		i++;
	}
	while (*line != '\0')
	{
		check_init(&check);
		check_check(line, &check);
		handle_line(&line, tab, check);
	}
	tab = expand(tab, env_list, 0);
	return (tab);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_status == 2)
		{
			g_status = 1;
			printf("\n");
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

static t_list	**allocation_list(char **tab)
{
	t_list	**list;

	list = NULL;
	list = (t_list **)malloc(sizeof(t_list *) * (count_pipe(tab) + 1) + 1);
	if (!list)
		exit(EXIT_FAILURE);
	return (list);
}

t_list	**parssing(char *line, t_env *env_list)
{
	char	**tab;
	t_list	**list;

	tab = NULL;
	list = NULL;
	if (ft_strlen(line) == 0)
		return (NULL);
	if (check_line(line) == 1)
	{
		handle_error();
		return (NULL);
	}
	if (count_quote(line) == 1)
		return (NULL);
	tab = handle_parssing(line, env_list);
	if (check_error(tab) == 1)
		return (NULL);
	list = allocation_list(tab);
	if (continue_parssing(list, tab, line) == 1)
		return (NULL);
	free_tab(tab);
	remove_quotes(list);
	list[0]->exit = 0;
	return (list);
}

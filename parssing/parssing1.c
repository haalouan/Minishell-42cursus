/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:38:45 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/23 16:23:14 by haalouan         ###   ########.fr       */
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

char	**handele_parssing(char *line)
{
	int		count;
	t_check	check;
	int		i;
	char	**tab;

	i = 0;
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
		handele_line(&line, tab, check);
	}
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
		handele_error();
		return (NULL);
	}
	if (count_quote(line) == 1)
		return (NULL);
	tab = handele_parssing(line);
	if (check_error(tab) == 1)
		return (NULL);
	list = (t_list **)malloc(sizeof(t_list *) * (count_pipe(tab) + 1) + 1);
	if (!list)
		exit(EXIT_FAILURE);
	if (continue_parssing(list, tab, line, env_list) == 1)
		return (NULL);
	// free_tab(tab);
	remove_quotes(list);
	list[0]->exit = 0;
	print_tab(list);//
	return (list);
}

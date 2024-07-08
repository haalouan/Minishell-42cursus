/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:46:15 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/06 21:39:19 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*protect_new_tab(char *str)
{
	int		i;
	int		k;
	char	*s;

	i = 1;
	k = 1;
	s = malloc(ft_strlen(str) + 1);
	if (!s)
		exit(EXIT_FAILURE);
	while (str && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		s[0] = '\"';
		s[k] = str[i];
		k++;
		i++;
	}
	s[k] = '\0';
	return (s);
}

static void	init(t_int *f, char **old_tab, char **new_str, char **new_tab)
{
	f->i = 0;
	f->j = 0;
	f->k = 0;
	f->size = ft_size(old_tab);
	f->size2 = ft_size(new_str);
	new_tab = safe_alloc(f->size + f->size2);
}

static void	change_tab2(char **new_str, char **new_tab, t_int *f)
{
	if (new_str[f->j][0] == '>' || new_str[f->j][0] == '<'
		|| new_str[f->j][0] == '|')
		new_str[f->j] = protect_new_str(new_str[f->j]);
	new_tab[f->i++] = new_str[f->j++];
}

char	**change_tab(char **old_tab, char *str)
{
	t_int	f;
	char	**new_str;
	char	**new_tab;

	new_str = ft_split(str, ' ');
	new_tab = NULL;
	init(&f, old_tab, new_str, new_tab);
	if (!new_str || f.size2 <= 1)
		return (old_tab);
	while (f.i < f.size + f.size2)
	{
		if (ft_strcmp(old_tab[f.k], str) == 0)
		{
			while (f.i < f.size + f.size2 && new_str && new_str[f.j])
				change_tab2(new_str, new_tab, &f);
			if (old_tab[f.k] && old_tab[f.k + 1])
				f.k++;
		}
		if (old_tab[f.k])
			new_tab[f.i++] = old_tab[f.k++];
	}
	new_tab[f.i] = NULL;
	free_tab(old_tab);
	return (new_tab);
}

char	**ft_realloc(char **tab, char *str)
{
	int		i;
	int		j;
	int		count;
	char	**new_tab;

	count = 0;
	i = 0;
	j = 0;
	while (tab && tab[count])
		count++;
	printf("%d\n", count);
	new_tab = safe_alloc(count);
	i = 0;
	while (i < count)
	{
		if (ft_strcmp(tab[i], str) == 0)
			i++;
		new_tab[j] = tab[i];
		i++;
		j++;
	}
	new_tab[j] = NULL;
	// free_tab(tab);
	return (new_tab);
}

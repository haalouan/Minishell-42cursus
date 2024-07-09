/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:57:59 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/09 12:09:39 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_dollar2(char *tab, int *i, int *k, int check)
{
	if (tab && tab[(*i)] == '\'' && check == 0)
	{
		(*i)++;
		while (tab && tab[(*i)] && tab[(*i)] != '\'')
			(*i)++;
		(*k) = (*i);
	}
}

static void	remove_dollar3(char *tab, int *i, int *chk)
{
	if (tab && tab[(*i)] == '$' && (*chk) == 0)
	{
		(*i)++;
		(*chk) = 1;
	}
}

char	*remove_dollar(char *tab, int check)
{
	int	i;
	int	k;
	int	chk;

	i = 0;
	k = 0;
	chk = 0;
	while (tab && tab[i] != '\0')
	{
		remove_dollar2(tab, &i, &k, check);
		remove_dollar3(tab, &i, &chk);
		tab[k] = tab[i];
		if (tab[i])
		{
			i++;
			k++;
		}
		else
			break ;
	}
	if (tab[k])
		tab[k] = '\0';
	return (tab);
}

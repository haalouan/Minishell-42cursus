/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:31:12 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/10 10:26:11 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_size(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**add_quotes(char **str)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new = NULL;
	while (str && str[i])
		i++;
	i--;
	new = malloc(ft_strlen(str[i]) + 3);
	if (!new)
		exit(EXIT_FAILURE);
	new[k++] = '\"';
	while (str && str[i] && str[i][j])
		new[k++] = str[i][j++];
	new[k] = '\"';
	new[k + 1] = '\0';
	str[i] = ft_substr(new, 0, ft_strlen(new));
	free(new);
	return (str);
}

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*protect_new_str(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	s = NULL;
	j = 1;
	if (!str)
		return (NULL);
	s = malloc(ft_strlen(str) + 3);
	if (!s)
		exit(EXIT_FAILURE);
	s[0] = '\"';
	while (str && str[i])
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\"';
	s[j + 1] = '\0';
	free(str);
	return (s);
}

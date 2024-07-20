/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:47:56 by achater           #+#    #+#             */
/*   Updated: 2024/07/20 14:51:13 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env *lst, int (*cmp)(char*, char*))
{
	if (lst == NULL)
		return ;
	while (lst)
	{
		if ((*cmp)(lst->key, "_") != 0 && lst->value != NULL)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else if ((*cmp)(lst->key, "_") != 0 && lst->value == NULL)
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}

int	key_exist(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	split_by_equal(char *str, char **key, char **value, int i)
{
	int	j;

	j = 0;
	if (str[i] == '=')
	{
		(*key) = NULL;
		(*value) = NULL;
		return ;
	}
	while (str[i] && str[i] != '=')
		i++;
	(*key) = malloc(i + 1);
	if (!(*key))
		error();
	i = -1;
	while (str[++i] && str[i] != '=')
		(*key)[i] = str[i];
	(*key)[i] = '\0';
	if (str[i] == '\0')
	{
		(*value) = NULL;
		return ;
	}
	(*value) = ft_strdup(str + i + 1);
}

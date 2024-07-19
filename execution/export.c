/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:50:01 by achater           #+#    #+#             */
/*   Updated: 2024/07/14 09:46:42 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_nodes(t_env *node1, t_env *node2)
{
	char *swap_key ;
	char *swap_value;

	swap_value = node1->value;
	swap_key = node1->key;
	node1->key = node2->key;
	node1->value = node2->value;
	node2->key = swap_key;
	node2->value = swap_value;
}


void	sort_and_print_env(t_env *lst, int (*cmp)(char*,char*))
{
	if (lst == NULL)
		return;
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
	t_env *tmp;

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
		return;
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
		return;
	}
	(*value) = ft_strdup(str + i + 1);
}

void	freee_list(t_env **env)
{
	t_env *tmp;
	t_env *tmp1;

	tmp = *env;
	while (tmp)
	{
		tmp1 = tmp->next;
		free(tmp->key);
		if (tmp->value == NULL)
			free(tmp->value);
		free(tmp);
		tmp = tmp1;
	}
	*env = NULL;
}
void	export_no_plus(char *key, char *value, t_env **env, t_env **tmp1)
{
	if (key_exist(*env, key) == 0)
		ft_lstadd_back(env, ft_lstnew(key, value));
	else
	{
		if (value == NULL)
		{
			free(key);
			return;
		}
		while(tmp1)
		{
			if (ft_strcmp((*tmp1)->key, key) == 0)
			{
				free((*tmp1)->value);
				(*tmp1)->value = value;
				break;
			}
			*tmp1 = (*tmp1)->next;
		}
		free(key);
	}
}

void	export_helper(char *key, char *value, t_env **env, t_env **tmp1)
{
	char *tmp;

	tmp = NULL;
	if (key[ft_strlen(key) - 1] != '+')
		return (export_no_plus(key, value, env, tmp1));
	key[ft_strlen(key) - 1] = '\0';
	if (key_exist(*env, key) == 0)
		return (ft_lstadd_back(env, ft_lstnew(key, value)));
	if (value == NULL)
		return (free(key));
	while(tmp1)
	{
		if (ft_strcmp((*tmp1)->key, key) == 0)
		{
			tmp = ft_strjoin((*tmp1)->value, value);
			free((*tmp1)->value);
			(*tmp1)->value = tmp;
			free(value);
			break ;
		}
		*tmp1 = (*tmp1)->next;
	}
	free(key);
}

void	error_hendler(char *key, char *value, int i)
{
	write(2, "minishell: export: `': not a valid identifier\n", 46);
	exit_status(1);
	if (i == 1)
		free(value);
	if (i == 0)
		free(key);
}
void	export_whith_args(char **args, t_env **tmp1, int i, t_env **env)
{
	char	*key;
	char	*value;

	while (args[++i])
	{
		if (args[i][0] == '\0')
		{
			write(2, "minishell: export: `': not a valid identifier\n", 46);
			exit_status(1);
			i++;
			continue;
		}
		split_by_equal(args[i], &key, &value, 0);
		if (key == NULL)
		{
			error_hendler(key, value, 1);
			continue;
		}
		if (check_args(key, "export") == 1
			|| (key[ft_strlen(key) - 1] == '+' && value == NULL))
			error_hendler(key, value, 0);
		else
			export_helper(key, value, env, tmp1);
	}
}

void	ft_export(char **args, t_env **env)
{
	t_env *tmp1;
	int i;

	i = -1;
	tmp1 = *env;
	if (args == NULL)
		sort_and_print_env(*env, ft_strcmp);
	else
		export_whith_args(args, &tmp1, i, env);
}

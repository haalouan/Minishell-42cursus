/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:50:01 by achater           #+#    #+#             */
/*   Updated: 2024/05/21 12:29:10 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_copy_list(t_env *env_list)
{
	t_env *new;
	t_env *tmp;

	new = NULL;
	tmp = env_list;
	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(tmp->key, tmp->value));
		tmp = tmp->next;
	}
	return (new);
}


void	sort_and_print_env(t_env *lst, int (*cmp)(char*,char*))
{
	char	*swap;
	char	*swap2;
	t_env	*tmp;

	tmp = lst;
	if(lst == NULL)
		return;
	while(lst->next != NULL)
	{
		if (((*cmp)(lst->key, lst->next->key)) > 0)
		{
			swap = lst->key;
			swap2 = lst->value;
			lst->value = lst->next->value;
			lst->key = lst->next->key;
			lst->next->key = swap;
			lst->next->value = swap2;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	while(lst)
	{
		if((*cmp)(lst->key, "_") != 0 && lst->value != NULL)
			printf("declare -x %s=\"%s\"\n", lst->key, lst->value);
		else if((*cmp)(lst->key, "_") != 0 && lst->value == NULL)
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
void	split_by_equal(char *str, char **key, char **value)
{
	int i = 0;
	int j = 0;

	if (str[i] == '=')
	{
		(*key) = NULL;
		(*value) = NULL;
		return;
	}
	while (str[i] && str[i] != '=')
		i++;
	(*key) = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		(*key)[i] = str[i];
		i++;
	}
	(*key)[i] = '\0';
	if(str[i] == '\0')
	{
		(*value) = NULL;
		return;
	}
	(*value) = malloc(ft_strlen(str) - i);
	i++;
	while (str[i])
	{
		(*value)[j] = str[i];
		i++;
		j++;
	}
	(*value)[j] = '\0';
}


void	ft_export(char **args, t_env **env)
{
	t_env *tmp;
	t_env *tmp1;
	int i = 0;
	char *key;
	char *value;

	tmp = ft_copy_list(*env);
	tmp1 = *env;
	if (args == NULL)
	{
		sort_and_print_env(tmp, ft_strcmp);
		return;
	}
	else
	{
		while (args[i])
		{
			if(args[i][0] == '\0')
			{
				printf("minishell: export: `': not a valid identifier\n");
				i++;
				continue;
			}
			split_by_equal(args[i], &key, &value);
			if (key == NULL)
			{
				printf("minishell: export: `=': not a valid identifier\n");
				i++;
				continue;
			}
			if (check_args(key, "export") == 1 || (key[ft_strlen(key) - 1] == '+' && value == NULL))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				i++;
				continue;
			}
			else
			{
				if (key[ft_strlen(key) - 1] != '+')
				{
					if (key_exist(*env, key) == 0)
						ft_lstadd_back(env, ft_lstnew(key, value));
					else
					{
						if (value == NULL)
						{
							i++;
							continue;
						}
						else
						{
							while(tmp1)
							{
								if (ft_strcmp(tmp1->key, key) == 0)
								{
									tmp1->value = value;
									break;
								}
								tmp1 = tmp1->next;
							}
						}
					}
				}
				else
				{
					key[ft_strlen(key) - 1] = '\0';
					if (key_exist(*env, key) == 0)
						ft_lstadd_back(env, ft_lstnew(key, value));
					else
						while(tmp1)
						{
							if (ft_strcmp(tmp1->key, key) == 0)
							{
								tmp1->value = ft_strjoin(get_env_value(key, tmp1), value);
								break;
							}
							tmp1 = tmp1->next;
						}
				}

			}
			i++;
		}
	}
}

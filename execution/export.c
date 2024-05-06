/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:50:01 by achater           #+#    #+#             */
/*   Updated: 2024/05/01 17:28:21 by achater          ###   ########.fr       */
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

void	ft_export(char **args, t_env **env)
{
	t_env *tmp;
	int i = 0;

	tmp = ft_copy_list(*env);
	if (args == NULL)
	{
		sort_and_print_env(tmp, ft_strcmp);
		return;
	}
	else
	{
		while (args[i])
		{
			if (check_args(args[i], "export") == 1)
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				return;
			}
			// else
			// {

			// }
			i++;
		}
	}
}
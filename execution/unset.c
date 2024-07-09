/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:24:13 by achater           #+#    #+#             */
/*   Updated: 2024/07/09 12:26:21 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_remove(t_env **env_list, char *key)
// {
// 	t_env *temp ;
// 	t_env *prev ;

// 	prev = NULL;
// 	temp = *env_list;
// 	while (env_list && temp->next != NULL)
// 	{
// 		if (check_args(key, "unset") == 1)
// 		{
// 			printf("minishell: unset: `%s': not a valid identifier\n", key);
// 			return ;
// 		}
// 		if (ft_strcmp(temp->key, key) != 0)
// 		{
// 			prev = temp;
// 			temp = temp->next;
// 		}
// 		if (prev == NULL && ft_strcmp(temp->key, key) == 0)
// 		{
// 			*env_list = temp->next;
// 			free(temp);
// 			return ;
// 		}
// 		else if (ft_strcmp(temp->key, key) == 0)
// 		{
// 			prev->next = temp->next;
// 			free(temp);
// 			return ;
// 		}
// 		if (temp->next == NULL && ft_strcmp(temp->key, key) == 0)
// 		{
// 			prev->next = NULL;
// 			free(temp);
// 			return ;
// 		}
// 	}
// 	return ;
// }
t_env	*find_node_to_remove(t_env **env_list, char *key)
{
    t_env	*temp;
    t_env	*prev;

    prev = NULL;
    temp = *env_list;
    while (temp != NULL)
    {
        if (ft_strcmp(temp->key, key) == 0)
            return (temp);
        prev = temp;
        temp = temp->next;
    }
    return (NULL);
}

void	remove_node(t_env **env_list, t_env *node_to_remove)
{
	t_env *temp;

	temp = *env_list;
	if (node_to_remove == NULL)
        	return ;
	if (*env_list == node_to_remove)
        	*env_list = node_to_remove->next;
	else
	{
		while (temp != NULL && temp->next != node_to_remove)
			temp = temp->next;
		if (temp != NULL)
			temp->next = node_to_remove->next;
	}
	free(node_to_remove);
}

void ft_remove(t_env **env_list, char *key)
{
    t_env *node_to_remove;

    node_to_remove = find_node_to_remove(env_list, key);
    remove_node(env_list, node_to_remove);
}

void	ft_unset(t_env **env_list, char **args)
{
	int i;

	i = 0;
	if (args == NULL)
		return ;
	if (env_list == NULL)
		return ;
	while (args[i])
	{
		if (check_args(args[i], "unset") == 1)
		{
			write(2, "minishell: unset: `': not a valid identifier\n", 46);
			exit_status(1);
			i++;
			continue ;
		}
		if (ft_strcmp(args[i], "_") == 0)
		{
			i++;
			continue ;
		}
		ft_remove(env_list, args[i]);
		i++;
	}
}

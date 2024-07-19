/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:48:07 by achater           #+#    #+#             */
/*   Updated: 2024/07/14 10:35:07 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (last)
		last -> next = new;
	else
		*lst = new;
}
t_env	*ft_lstlast(t_env *lst)
{
	t_env	*x;

	if (!lst)
		return (NULL);
	x = lst;
	while (x-> next)
		x = x-> next;
	return (x);
}

t_env	*ft_lstnew(char *key , char *content)
{
	t_env	*x;
	x = malloc(sizeof(t_env));
	if (x == 0)
		return (0);
	x ->key = key;
	x ->value = content;
	x ->next = NULL;
	return (x);
}
int	ft_lstsize(t_env *lst)
{
	int		i;
	t_env	*x;

	x = lst;
	i = 0;
	while (x)
	{
		i++;
		x = x ->next;
	}
	return (i);
}

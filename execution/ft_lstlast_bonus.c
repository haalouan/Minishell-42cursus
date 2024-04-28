/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:17:37 by achater           #+#    #+#             */
/*   Updated: 2024/04/28 15:38:12 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

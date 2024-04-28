/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:39:53 by achater           #+#    #+#             */
/*   Updated: 2024/04/28 15:38:12 by achater          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:45:21 by achater           #+#    #+#             */
/*   Updated: 2024/04/28 15:38:12 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

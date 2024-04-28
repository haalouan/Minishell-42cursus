/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:52 by achater           #+#    #+#             */
/*   Updated: 2024/04/28 15:38:12 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *arg, char *str)
{
	int i;

	i = 0;
	while (arg[i] && str[i])
	{
		if (arg[i] != str[i])
			return (1);
		i++;
	}
	if (arg[i] != str[i])
		return (1);
	return (0);
}

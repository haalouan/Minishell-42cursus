/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:49 by achater           #+#    #+#             */
/*   Updated: 2024/07/21 11:26:11 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	check_args_unset(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
			return (1);
		if (ft_is_alpha(args[i]) == 0 && args[i] != '_'
			&& (args[i] < '0' || args[i] > '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_args_export(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
			return (1);
		if (ft_is_alpha(args[i]) == 0 && args[i] != '_'
			&& (args[i] < '0' || args[i] > '9')
			&& args[i] != '=' && (args[i] != '+'))
			return (1);
		if (args[i] == '+' && i != (int)ft_strlen(args) - 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_args(char *args, char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "unset") == 0)
	{
		if (check_args_unset(args) == 1)
			return (1);
	}
	else
		if (check_args_export(args) == 1)
			return (1);
	return (0);
}

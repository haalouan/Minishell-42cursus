/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:52 by achater           #+#    #+#             */
/*   Updated: 2024/04/30 15:11:07 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *arg, char *str)
{
	int i;

	i = 0;
	while (arg[i] && str[i])
	{
		if (arg[i] > str[i])
			return (1);
		if (arg[i] < str[i])
			return (-1);
		i++;
	}
	if (arg[i] == '\0' && str[i] != '\0')
		return (-1);
	if (arg[i] != '\0' && str[i] == '\0')
		return (1);
	return (0);
}
int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int check_args(char *args,char *str)
{
	int i;

	i = 0;
	if (ft_strcmp(str, "unset") == 0)
		while(args[i])
		{
			if(i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
				return (1);
			if(ft_is_alpha(args[i]) == 0 && args[i] != '_' && (args[i] < '0' || args[i] > '9'))
				return (1);
			i++;
		}
	else
		while(args[i])
		{
			if(i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
				return (1);
			if(ft_is_alpha(args[i]) == 0 && args[i] != '_' && (args[i] < '0' || args[i] > '9')
				&& args[i] != '=' && (args[i] != '+'))
				return (1);
			if(args[i] == '+' && args[i + 1] != '=')
				return (1);
			i++;
		}
	return (0);
}

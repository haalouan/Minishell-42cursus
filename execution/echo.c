/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:20:41 by achater           #+#    #+#             */
/*   Updated: 2024/08/06 11:35:33 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	cmp(char *s1)
{
	int	i;

	i = 0;
	if (s1[i] == '-' && s1[i + 1] == 'n')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	f_help(int *n, int *j, int *x)
{
	(*j)++;
	*n = 1;
	*x = 1;
}

void	ft_echo(char **args, int n, int j, int x)
{
	if (args == NULL)
	{
		ft_putstr("\n");
		exit_status(0);
		return ;
	}
	if (cmp(args[0]) == 0)
		f_help(&n, &j, &x);
	while (args[j])
	{
		if (cmp(args[j]) == 0 && n == 1)
		{
			j++;
			continue ;
		}
		if (cmp(args[j]) != 0)
			n = 0;
		ft_putstr(args[j]);
		if (args[j + 1])
			ft_putstr(" ");
		j++;
	}
	if (x == 0)
		ft_putstr("\n");
	exit_status(0);
}

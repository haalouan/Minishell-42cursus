/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:20:41 by achater           #+#    #+#             */
/*   Updated: 2024/06/30 11:27:08 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("\n");
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
		printf("%s", args[j]);
		if (args[j + 1])
			printf(" ");
		j++;
	}
	if (x == 0)
		printf("\n");
}

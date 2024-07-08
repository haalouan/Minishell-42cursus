/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:49 by achater           #+#    #+#             */
/*   Updated: 2024/07/03 10:58:58 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	check_args(char *args, char *str)
{
	int	i;

	i = 0;
	if (ft_strcmp(str, "unset") == 0)
		while (args[i])
		{
			if (i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
				return (1);
			if (ft_is_alpha(args[i]) == 0 && args[i] != '_' && (args[i] < '0' || args[i] > '9'))
				return (1);
			i++;
		}
	else
		while (args[i])
		{
			if (i == 0 && ft_is_alpha(args[i]) == 0 && args[i] != '_')
				return (1);
			if (ft_is_alpha(args[i]) == 0 && args[i] != '_' && (args[i] < '0' || args[i] > '9')
				&& args[i] != '=' && (args[i] != '+'))
				return (1);
			if (args[i] == '+' && i != (int)ft_strlen(args) - 1)
				return (1);
			i++;
		}
	return (0);
}

char	*ft_strjoin(char *s1,char *s2)
{
	char *s3;
	int i;
	int j;

	i = -1;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(s3 == NULL)
		return(NULL);
	if(s1 == NULL)
		return(s2);
	if(s2 == NULL)
		return(s1);
	while(s1[++i])
		s3[i] = s1[i];
	while(s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return(s3);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	count_args0(char **args)
{
	int i;

	i = 0;
	while(args[i])
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:23:28 by achater           #+#    #+#             */
/*   Updated: 2024/08/02 10:37:51 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2, int i, int j)
{
	char	*s3;

	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		free(s3);
		return (s2);
	}
	if (s2 == NULL)
	{
		free(s3);
		return (s1);
	}
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	(1) && (free(s1), free(s2), s3[i] = '\0');
	return (s3);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = -1;
	j = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s3 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	while (s1[++i])
		s3[i] = s1[i];
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s2);
	return (s3);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

int	count_args0(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	error_handling(char *cmd, char *str, int i, int x)
{
	write(2, "minishell:", 10);
	write(2, cmd, ft_strlen(cmd));
	write(2, str, i);
	write(2, "\n", 1);
	exit(x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:52 by achater           #+#    #+#             */
/*   Updated: 2024/08/03 11:15:08 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *arg, char *str)
{
	int	i;

	i = 0;
	if (!arg || !str)
		return (0);
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

static int	f(char *s4, char *s2, char *s1, char *s3)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	while (s1[i])
	{
		s4[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s4[i] = s2[j];
		i++;
		j++;
	}
	while (s3[k])
	{
		s4[i] = s3[k];
		i++;
		k++;
	}
	return (i);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*s4;
	int		i;
	size_t	i1;
	size_t	i2;
	size_t	i3;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	i3 = ft_strlen(s3);
	s4 = malloc(i1 + i2 + i3 + 1);
	if (s4 == NULL)
		return (NULL);
	i = f(s4, s2, s1, s3);
	s4[i] = '\0';
	return (s4);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while ((i < len) && haystack[i])
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0'
			&& (i + j) < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
		j = 0;
	}
	return (NULL);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	neg;

	x = 0;
	i = 0;
	neg = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		x = (x * 10) + str[i] - '0';
		i++;
	}
	return (x * neg);
}

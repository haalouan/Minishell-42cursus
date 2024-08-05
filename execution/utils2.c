/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:51:56 by achater           #+#    #+#             */
/*   Updated: 2024/08/03 11:14:16 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	f_itoa(int i, char *x, int len, long nb)
{
	while ((len) > 0)
	{
		x[len - 1 + i] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
}

static int	count_itoa(int n)
{
	int		x;
	long	nb;

	nb = n;
	x = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char	*x;
	int		len;
	int		i;
	long	nb;

	nb = n;
	len = count_itoa(nb);
	i = 0;
	if (n < 0)
		i = 1;
	x = malloc(sizeof(char) * len + i + 1);
	if (!x)
		return (NULL);
	if (n < 0)
	{
		x[0] = '-';
		nb *= -1;
	}
	f_itoa(i, x, len, nb);
	x[len + i] = '\0';
	return (x);
}

char	*shlvl_increment(char *str)
{
	int	i;

	if (!str)
		return (ft_strdup("1"));
	i = ft_atoi(str);
	if (i >= 1000)
	{
		free(str);
		return (ft_strdup("1"));
	}
	i++;
	if (i == 1000)
	{
		free(str);
		return (ft_strdup(""));
	}
	free(str);
	return (ft_itoa(i));
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

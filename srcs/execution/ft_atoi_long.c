/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 12:28:30 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/12 17:06:56 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\v' || c == '\r' || c == '\t' || c == '\n'
		|| c == '\f')
	{
		return (1);
	}
	return (0);
}

long	ft_atoi_long(char *s)
{
	long int	number;
	int			sign;
	int			i;

	number = 0;
	sign = 1;
	i = 0;
	while (*s && ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && *s == '0')
		s++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = (number * 10) + (s[i++] - 48);
	}
	return (number * sign);
}

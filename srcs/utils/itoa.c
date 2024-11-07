/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:13 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/12 17:05:25 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*last_argument(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!str[i + 1])
			return (str[i]);
		i++;
	}
	return (str[i]);
}

static int	ft_len_num(long int n)
{
	int			i;
	long int	div;

	i = 0;
	div = 1;
	while (div <= n)
	{
		div *= 10;
		i++;
	}
	return (i);
}

static char	*ft_set_number(char *s, long int n, size_t len)
{
	s[len] = '\0';
	while (n >= 1)
	{
		s[len-- - 1] = n % 10 + 48;
		n /= 10;
	}
	return (s);
}

char	*ft_itoa(int nb)
{
	char		*s;
	long int	n;
	size_t		len;
	size_t		sign;

	len = 0;
	n = nb;
	sign = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		sign = 1;
		len++;
		n = -n;
	}
	len += ft_len_num(n);
	s = malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s = ft_set_number(s, n, len);
	if (sign)
		s[0] = '-';
	return (s);
}

char	*ft_calloc(int size)
{
	char	*buffer;

	buffer = malloc(size);
	ft_bzero(buffer, size);
	return (buffer);
}

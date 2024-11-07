/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:35 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:25:36 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*pointer;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	pointer = (char *)malloc(len1 + len2 + 1);
	if (pointer == NULL)
		return (NULL);
	if (s1)
	{
		ft_memcpy(pointer, s1, len1);
		free(s1);
	}
	if (s2)
	{
		ft_memcpy(pointer + len1, s2, len2);
		free(s2);
	}
	pointer[len1 + len2] = '\0';
	return (pointer);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_bzero(char *str, int size)
{
	int	i;

	i = 0;
	while (i < size)
		str[i++] = 0;
}

int	copy_nb(t_node *content, char *buffer, int k)
{
	int	j;
	int	max;

	j = content->exit_nb;
	max = 1;
	if (j == 0)
		buffer[k++] = 48;
	while (j >= max)
		max *= 10;
	max /= 10;
	while (max > 0)
	{
		buffer[k] = j / max + 48;
		k++;
		j -= (j / max) * max;
		max /= 10;
	}
	return (k);
}

void	update_syntax_status(char x)
{
	char	*c;

	c = ft_global_syntax_check();
	if (!*c)
		*c = x;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:23:20 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:22:56 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp_n(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1[i])
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i])
		return (0);
	while (s1[i])
	{
		if (s1[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print(t_command *content, int i)
{
	while (content->options[i] && ft_strcmp_n(content->options[i], "-n"))
		i++;
	while (content->options[i])
	{
		write(1, content->options[i], ft_strlen(content->options[i]));
		if (content->options[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	handle_echo(t_command *content, t_hold **env, t_node *node)
{
	int	i;

	i = 1;
	if (content->options[1] && ft_strcmp_n(content->options[1], "-n"))
		print(content, i);
	else
	{
		while (content->options[i])
		{
			write(1, content->options[i], ft_strlen(content->options[i]));
			if (content->options[i + 1])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
	node->exit_nb = 0;
	(void)env;
	(void)node;
}

void	print_cd_error(t_command *content, t_node *node)
{
	if (!content->options[1])
		write(2, " cd: missing argument\n", 23);
	else if (content->options[1] && content->options[2])
		write(2, " cd: too many arguments\n", 25);
	node->exit_nb = 1;
}

unsigned char	unsigned_char_atoi(char *str)
{
	size_t	number;
	int		negative;

	number = 0;
	negative = 0;
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - 48);
		str++;
	}
	if (negative)
		number *= -1;
	return (number);
}

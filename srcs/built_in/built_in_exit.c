/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:23:37 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/30 15:44:04 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_numeric(char *str)
{
	int		count;
	size_t	number;
	int		negative;

	negative = 0;
	count = 0;
	number = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		number = number * 10 + (*str++ - 48);
		count++;
	}
	if (count >= 20 || number - negative > __LONG_MAX__)
		return (0);
	return (1);
}

int	ft_atoi_recursive(char *str, int result)
{
	if (!str || *str == '\0')
	{
		return (result);
	}
	if (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		return (ft_atoi_recursive(str + 1, result));
	}
	return (result);
}

int	ft_atoi(char *str)
{
	return (ft_atoi_recursive(str, 0));
}

void	handle_exit(t_command *content, t_hold **env, t_node *node)
{
	int	i;

	(void)*env;
	i = 1;
	while (content->options[i])
	{
		if (!is_numeric(content->options[i]) && i == 1)
		{
			write(2, "exit\n", 6);
			write(2, "numeric argument required\n", 27);
			exit(2);
		}
		i++;
	}
	if (i > 2)
	{
		write(2, "exit\n", 6);
		write(2, "Too many arguments \n", 21);
		node->exit_nb = 1;
		return ;
	}
	exit(unsigned_char_atoi(content->options[1]));
}

void	add_default(char *str, t_hold **env)
{
	char	buffer_1[2048];
	char	buffer_2[2048];

	ft_bzero(buffer_1, 2048);
	ft_bzero(buffer_2, 2048);
	ft_add_env(env, ft_new_env(find_key(str, buffer_1), find_value(str,
				buffer_2)));
}

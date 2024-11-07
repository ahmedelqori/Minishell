/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:23:27 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:22:07 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_env(char *str, t_hold **env)
{
	char	buffer_1[2048];
	char	buffer_2[2048];
	t_hold	*current;

	current = *env;
	ft_bzero(buffer_1, 2048);
	ft_bzero(buffer_2, 2048);
	while (current)
	{
		if (ft_strcmp_2(find_key(str, buffer_1), current->key))
		{
			if (find_value(str, buffer_2))
			{
				ft_bzero(buffer_2, 2048);
				if (current->value)
					free(current->value);
				current->value = ft_strdup(find_value(str, buffer_2));
			}
			return ;
		}
		current = current->next;
	}
	add_default(str, env);
}

void	print_env(t_hold *current)
{
	if (current->value)
	{
		write(1, current->key, ft_strlen(current->key));
		write(1, "=", 1);
		write(1, current->value, ft_strlen(current->value));
		write(1, "\n", 1);
	}
	else
	{
		write(1, current->key, ft_strlen(current->key));
		write(1, "\n", 1);
	}
}

void	print(t_hold *env)
{
	t_hold	*current;

	current = env;
	current = env;
	while (current)
	{
		print_env(current);
		current = current->next;
	}
}

void	handle_export(t_command *content, t_hold **env, t_node *node)
{
	int		i;
	int		f;
	char	buffer[2048];

	ft_bzero(buffer, 2048);
	if (!content->options[1])
		print(*env);
	else if (ft_lstsize(node->command) == 1)
	{
		i = 1;
		while (content->options[i])
		{
			f = 0;
			if (!check_export(content->options[i], &f))
			{
				find_key(content->options[i], buffer);
				print_export_error(buffer);
				ft_bzero(buffer, 2048);
			}
			else
				modify_env(content->options[i], env);
			i++;
		}
	}
	node->exit_nb = f;
}

void	del_env(char *str, t_hold **env)
{
	t_hold	*current;
	char	buffer[2048];
	t_hold	*prev;

	ft_bzero(buffer, 2048);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp_2(current->key, str))
		{
			if (prev == NULL)
				*env = current->next;
			else
				prev->next = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

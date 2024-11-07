/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:23:42 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:21:32 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstsize(t_command *command)
{
	t_command	*current;
	int			i;

	current = command;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	*modify_pwd(t_hold **env, char *s1, char *s2, char *new)
{
	t_hold	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp_2(new, current->key))
		{
			if (current->value)
			{
				copy(current->value, s1);
				free(current->value);
			}
			getcwd(s2, 2048);
			current->value = ft_strdup(s2);
		}
		current = current->next;
	}
	return (s1);
}

void	handle_cd(t_command *content, t_hold **env, t_node *node)
{
	DIR	*dir;

	if (content->options[1] && !content->options[2])
	{
		dir = opendir(content->options[1]);
		if (dir == NULL)
		{
			perror(content->options[1]);
			node->exit_nb = 1;
			closedir(dir);
			return ;
		}
		closedir(dir);
		if (ft_lstsize(node->command) == 1)
		{
			chdir(content->options[1]);
			change_pwd(env);
		}
	}
	else
	{
		print_cd_error(content, node);
		return ;
	}
	node->exit_nb = 0;
}

int	check_export(char *str, int *f)
{
	char	buffer[2048];
	int		i;

	ft_bzero(buffer, 2048);
	find_key(str, buffer);
	if (!*buffer)
		*f = 1;
	i = 0;
	while (buffer[i])
	{
		if (i == 0 && (!is_alpha(buffer[i]) && buffer[i] != '_'))
			*f = 1;
		else if (i > 0 && (!is_alpha(buffer[i]) && !is_num(buffer[i])))
			*f = 1;
		i++;
	}
	if (*f == 1)
		return (0);
	return (1);
}

void	print_export_error(char *str)
{
	write(2, " export: ", 10);
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
}

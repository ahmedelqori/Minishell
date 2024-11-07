/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:23:32 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:20:59 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_env(t_command *content, t_hold **env, t_node *node)
{
	t_hold	*current;

	(void)*node;
	(void)*content;
	current = *env;
	while (current)
	{
		if (current->value)
		{
			write(1, current->key, ft_strlen(current->key));
			write(1, "=", 1);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\n", 1);
		}
		current = current->next;
	}
	node->exit_nb = 0;
}

void	copy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
}

void	handle_unset(t_command *content, t_hold **env, t_node *node)
{
	int	i;

	(void)*node;
	i = 1;
	if (ft_lstsize(node->command) == 1)
	{
		while (content->options[i])
		{
			del_env(content->options[i], env);
			i++;
		}
	}
	node->exit_nb = 0;
}

void	change_pwd(t_hold **env)
{
	t_hold	*current;
	char	*old;
	char	*new;
	char	*s1;
	char	*s2;

	old = "OLDPWD";
	new = "PWD";
	s1 = ft_calloc(2048);
	s2 = ft_calloc(2048);
	s1 = modify_pwd(env, s1, s2, new);
	current = *env;
	while (current)
	{
		if (ft_strcmp_2(old, current->key))
		{
			if (current->value)
				free(current->value);
			current->value = ft_strdup(s1);
		}
		current = current->next;
	}
	free(s1);
	free(s2);
}

void	handle_pwd(t_command *content, t_hold **env, t_node *node)
{
	char	*pwd;
	t_hold	*current;

	(void)*content;
	(void)*node;
	pwd = "PWD";
	current = *env;
	while (current)
	{
		if (ft_strcmp_2(pwd, current->key))
		{
			write(1, current->value, ft_strlen(current->value));
			write(1, "\n", 1);
			return ;
		}
		current = current->next;
	}
	node->exit_nb = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:26 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/12 17:06:11 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirect(t_redirect **lst)
{
	t_redirect	*current;
	t_redirect	*next_node;

	current = *lst;
	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

t_redirect	*ft_new_redirect(char *buffer, int k)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->str = ft_strdup(buffer);
	new->flag = k;
	new->next = NULL;
	return (new);
}

void	ft_add_redirect(t_redirect **lst, t_redirect *new)
{
	t_redirect	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	set_default(t_hold **lst)
{
	char	buffer[2048];

	ft_bzero(buffer, 2048);
	ft_add_env(lst, ft_new_env("PWD", getcwd(buffer, 2048)));
	ft_add_env(lst, ft_new_env("SHLVL", "0"));
	ft_add_env(lst, ft_new_env("_", "./minishell"));
}

void	change_variable(t_hold **env, t_command *command)
{
	t_command	*current;
	char		buffer[2048];
	t_hold		*tmp;

	ft_bzero(buffer, 2048);
	current = command;
	while (current->next)
		current = current->next;
	tmp = *env;
	if (!tmp)
		ft_add_env(env, ft_new_env("_", last_argument(current->options)));
	while (tmp)
	{
		if (ft_strcmp_2("_", tmp->key))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(last_argument(current->options));
		}
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:02 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:25:57 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_hold **lst)
{
	t_hold	*current;
	t_hold	*next_node;

	current = *lst;
	while (current)
	{
		next_node = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

t_hold	*ft_new_env(char *buffer, char *buffer_2)
{
	t_hold	*new;

	new = malloc(sizeof(t_hold));
	if (!new)
		return (NULL);
	new->key = ft_strdup(buffer);
	new->value = ft_strdup(buffer_2);
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_hold **lst, t_hold *new)
{
	t_hold	*current;

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

char	*find_key(char *str, char *buffer)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		buffer[i] = str[i];
		i++;
	}
	return (buffer);
}

void	initialize_env(t_hold **lst, char **env)
{
	char	buffer_1[2048];
	char	buffer_2[2048];
	int		i;

	ft_bzero(buffer_1, 2048);
	ft_bzero(buffer_2, 2048);
	i = 0;
	if (!env[i])
	{
		set_default(lst);
		return ;
	}
	while (env[i])
	{
		ft_add_env(lst, ft_new_env(find_key(env[i], buffer_1),
				find_value(env[i], buffer_2)));
		ft_bzero(buffer_1, 2048);
		ft_bzero(buffer_2, 2048);
		i++;
	}
}

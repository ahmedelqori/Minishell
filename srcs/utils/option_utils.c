/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:22 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:24:25 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_del_option(t_option **lst)
{
	t_option	*current;

	current = *lst;
	free(current->str);
	free(current);
	*lst = NULL;
}

void	free_option(t_option **lst)
{
	t_option	*current;
	t_option	*next_node;

	current = *lst;
	while (current)
	{
		next_node = current->next;
		ft_del_option(&current);
		current = next_node;
	}
	*lst = NULL;
}

t_option	*ft_new_option(char *buffer)
{
	t_option	*new;

	new = malloc(sizeof(t_option));
	if (!new)
		return (NULL);
	new->str = ft_strdup(buffer);
	new->next = NULL;
	return (new);
}

void	ft_add_option(t_option **lst, t_option *new)
{
	t_option	*current;

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

int	ft_listsize(t_option *node)
{
	int	size;

	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

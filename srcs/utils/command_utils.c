/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:57 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:24:58 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*ft_last_command(t_command *node)
{
	t_command	*current;

	current = node;
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_del_command(t_command **lst)
{
	t_command	*current;
	int			i;

	current = *lst;
	i = 0;
	while (current->options[i])
		free(current->options[i++]);
	free(current->options);
	free_option(&current->node_options);
	free_redirect(&current->redirection);
	free(current);
}

void	free_command(t_command **lst)
{
	t_command	*current;
	t_command	*next_node;

	current = *lst;
	while (current)
	{
		next_node = current->next;
		ft_del_command(&current);
		current = next_node;
	}
	*lst = NULL;
}

t_command	*ft_new_command(void)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->redirection = NULL;
	new->node_options = NULL;
	new->options = malloc(sizeof(char *));
	new->syntax = 0;
	*(new->options) = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*current;

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

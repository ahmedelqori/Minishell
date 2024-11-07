/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:32 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:35:01 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	split_str(t_command *lst)
{
	int			i;
	t_command	*current;
	t_option	*options;

	current = lst;
	while (current)
	{
		i = ft_listsize(current->node_options);
		free(current->options);
		current->options = malloc((i + 1) * sizeof(char *));
		options = current->node_options;
		i = 0;
		while (options)
		{
			current->options[i] = ft_strdup(options->str);
			i++;
			options = options->next;
		}
		current->options[i] = NULL;
		current = current->next;
	}
}

void	split_parsing(t_node *content, char *s)
{
	if (!split_command(s))
		update_syntax_status('s');
	split_str(content->command);
}

void	print_error(t_node *node)
{
	char	*c;

	c = ft_global_syntax_check();
	if (*c)
	{
		if (*c == 's')
			write(2, "syntax error\n", 14);
		else if (*c == 'r')
		{
			write(2, "ambigious redirect\n", 20);
			*c = 0;
			return ;
		}
		*c = 0;
		node->exit_nb = 2;
	}
}

void	redirect_error(t_node *content)
{
	char	*c;

	c = ft_global_syntax_check();
	if (*c != 's')
	{
		update_syntax_status('r');
		content->exit_nb = 1;
		ft_last_command(content->command)->syntax = 'r';
	}
}

void	escape_space(char **s1, char **s2)
{
	char	*temp;
	char	*tmp;

	temp = *s1;
	tmp = *s2;
	if (*temp == ' ' || *temp == '\t')
		*tmp++ = *temp++;
	while (*temp == ' ' || *temp == '\t')
		temp++;
	*s1 = temp;
	*s2 = tmp;
}

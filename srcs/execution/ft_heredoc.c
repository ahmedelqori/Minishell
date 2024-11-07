/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:02:58 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/31 17:25:29 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_delete_all_here_doc(t_command *list)
{
	t_command	*command;
	t_redirect	*inputs;

	command = list;
	while (command)
	{
		inputs = command->redirection;
		while (inputs)
		{
			if (inputs->flag == 1)
			{
				unlink(inputs->str);
			}
			inputs = inputs->next;
		}
		command = command->next;
	}
}

char	*expand_line(char *str, t_hold *env, t_node *content)
{
	char	buffer[2048];
	char	*temp;
	int		i;

	i = 0;
	temp = str;
	ft_bzero(buffer, 2048);
	while (*temp)
	{
		if (*temp == '$' && *(temp + 1) != ' ' && *(temp + 1) && *(temp
				+ 1) != '?')
			i = handle_variable(&temp, buffer, env, i);
		else if (*temp == '$' && *(temp + 1) == '?')
		{
			i = copy_nb(content, buffer, i);
			temp += 2;
		}
		else if (*temp)
			buffer[i++] = *temp++;
	}
	free(str);
	return (ft_strdup(buffer));
}

int	ft_count_here_doc(int *i, t_redirect *redirection)
{
	t_redirect	*cur;

	cur = redirection;
	while (cur)
	{
		if (cur->flag == 1)
			*i += 1;
		cur = cur->next;
	}
	if (*i > 16)
	{
		write(2, MAX_HERE_DOC, ft_strlen(MAX_HERE_DOC));
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_count_all_here_doc(t_command *cur, t_node *list)
{
	t_command	*heredoc;
	int			i;

	i = 0;
	heredoc = cur;
	while (heredoc)
	{
		if (ft_count_here_doc(&i, heredoc->redirection) == FAIL)
		{
			list->exit_nb = 2;
			exit(2);
		}
		heredoc = heredoc->next;
	}
	return (SUCCESS);
}

int	ft_handle_heredoc(t_node *list, t_hold *env)
{
	t_command	*cur;
	t_redirect	*input;

	cur = list->command;
	if (ft_count_all_here_doc(cur, list) == FAIL)
		return (FAIL);
	while (cur)
	{
		input = cur->redirection;
		while (input)
		{
			if (input->flag == 1)
			{
				if (ft_help_here_doc(list, env, input) == FAIL)
				{
					ft_delete_all_here_doc(list->command);
					return (FAIL);
				}
			}
			input = input->next;
		}
		cur = cur->next;
	}
	return (SUCCESS);
}

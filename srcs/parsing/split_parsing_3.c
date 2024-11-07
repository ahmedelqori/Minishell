/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:38 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:16:33 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	helper(char **s, char **buffer, t_hold *env, t_node *content)
{
	char	*temp;
	char	*tmp;

	tmp = *buffer;
	temp = *s;
	if (*(temp + 1) == '?')
	{
		tmp = (*buffer) + copy_nb(content, tmp, (tmp - (*buffer)));
		temp += 2;
	}
	else if (is_alpha(*(temp + 1)) || *(temp + 1) == '_')
		tmp = (*buffer) + handle_variable(&temp, tmp, env, (tmp - (*buffer)));
	else
		*tmp++ = *temp++;
	*buffer = tmp;
	*s = temp;
}

void	copy_content(t_node *content, t_option *list)
{
	t_option	*current;

	current = list;
	while (current)
	{
		ft_add_option(&ft_last_command(content->command)->node_options,
			ft_new_option(current->str));
		current = current->next;
	}
}

char	*expand_redirection(t_node *content, char *str, int flag, t_hold *env)
{
	t_option	*list;

	if (!*str)
	{
		update_syntax_status('s');
		return (str);
	}
	if (flag != 1)
		str = expand_buffer(str, env, content);
	else
	{
		ft_add_redirect(&ft_last_command(content->command)->redirection,
			ft_new_redirect(str, flag));
		return (str);
	}
	list = helper2(str);
	if (ft_listsize(list) > 1 || !*str)
		redirect_error(content);
	else
		ft_add_redirect(&ft_last_command(content->command)->redirection,
			ft_new_redirect(list->str, flag));
	free_option(&list);
	return (str);
}

void	increment_pointer(char **s1, char **s2)
{
	char	*s;
	char	*p;

	s = *s1;
	p = *s2;
	s++;
	p++;
	*s1 = s;
	*s2 = p;
}

int	ismatch(char *s, char *p, char *ss, char *pp)
{
	while (*s != '\0')
	{
		if (*p == '"' || *p == '\'')
		{
			if (!escape_quote(&s, &p))
				return (0);
		}
		else if (*p == *s && *p != '*')
			increment_pointer(&s, &p);
		else if (*p == '*')
		{
			ss = s;
			pp = p++;
		}
		else if (pp != NULL)
		{
			s = ss++;
			p = pp + 1;
		}
		else
			return (0);
	}
	while (*p == '*')
		p++;
	return ((*s == '\0' && *p == '\0'));
}

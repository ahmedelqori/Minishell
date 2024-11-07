/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wilcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:47 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/12 17:02:24 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_option	*helper5(t_option **current, char *str, char *ss, char *pp)
{
	t_option	*tmp;
	t_option	*temp;

	temp = NULL;
	tmp = *current;
	while (tmp)
	{
		if (ismatch(tmp->str, str, ss, pp) && *tmp->str != '.')
			ft_add_option(&temp, ft_new_option(tmp->str));
		tmp = tmp->next;
	}
	free_option(current);
	return (temp);
}

t_option	*matching_list(char *str, char *ss, char *pp, char *buffer)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	t_option		*current;

	current = NULL;
	pdir = opendir(buffer);
	if (!pdir)
		return (NULL);
	pdirent = readdir(pdir);
	while (pdirent != NULL)
	{
		ft_add_option(&current, ft_new_option(pdirent->d_name));
		pdirent = readdir(pdir);
	}
	closedir(pdir);
	return (helper5(&current, str, ss, pp));
}

char	*copy_str(char *s)
{
	int		i;
	char	buffer[2048];
	char	c;
	int		k;

	i = 0;
	k = 0;
	ft_bzero(buffer, 2048);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				buffer[k++] = s[i++];
			if (s[i])
				i++;
		}
		else
			buffer[k++] = s[i++];
	}
	free(s);
	return (ft_strdup(buffer));
}

char	*expand_command(t_node *content, char *str, t_hold *env)
{
	t_option	*list;
	t_option	*current;

	str = expand_buffer(str, env, content);
	if (!*str)
		return (str);
	list = helper2(str);
	current = list;
	while (current)
	{
		ft_add_option(&ft_last_command(content->command)->node_options,
			ft_new_option(current->str));
		current = current->next;
	}
	free_option(&list);
	return (str);
}

int	has_quote(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:28 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/30 15:45:32 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_list(t_option *list1, t_option **list2)
{
	t_option	*current;

	current = list1;
	while (current)
	{
		ft_add_option(list2, ft_new_option(current->str));
		current = current->next;
	}
}

void	insert(t_option **list, char *buffer)
{
	char		*ss;
	char		*pp;
	char		*temp;
	t_option	*tmp;

	temp = ft_calloc(2048);
	ss = NULL;
	pp = NULL;
	getcwd(temp, 2048);
	tmp = matching_list(buffer, ss, pp, temp);
	if (tmp)
		copy_list(tmp, list);
	else
	{
		buffer = copy_str(buffer);
		ft_add_option(list, ft_new_option(buffer));
	}
	free_option(&tmp);
	free(temp);
	free(buffer);
}

t_option	*split_str_2(char *str)
{
	t_option	*list;
	char		*buffer;
	char		*temp;

	buffer = ft_calloc(2048);
	temp = buffer;
	list = NULL;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			parsing_quote(&temp, &str);
		if (*str && *str != ' ' && *str != '\t')
			*temp++ = *str++;
		if (*str == ' ' || *str == '\t' || !*str)
		{
			insert(&list, buffer);
			buffer = ft_calloc(2048);
			temp = buffer;
			while (*str == '\t' || *str == ' ')
				str++;
		}
	}
	free(buffer);
	return (list);
}

t_option	*helper2(char *str)
{
	t_option	*list;

	list = split_str_2(str);
	return (list);
}

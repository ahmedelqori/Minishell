/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:20:08 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/01 12:27:11 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_put_env_arr_2(t_hold *t)
{
	char	*tmp;
	t_hold	*cur;

	cur = t;
	if (!cur)
		return ;
	while (cur)
	{
		if (ft_strcmp_1(cur->key, "SHLVL") == 0)
		{
			tmp = ft_itoa(ft_atoi_long(cur->value) + 1);
			free(cur->value);
			cur->value = tmp;
		}
		cur = cur->next;
	}
}

int	ft_openfiles_output_append(char *str, int n)
{
	int	fd;

	if (n == 0)
	{
		fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		if (fd == -1)
		{
			perror("open:");
			return (FAIL);
		}
	}
	else
	{
		fd = open(str, O_CREAT | O_APPEND | O_WRONLY, 0664);
		if (fd == -1)
		{
			perror("open:");
			return (FAIL);
		}
	}
	return (fd);
}

int	ft_is_any_file(t_redirect *tmp, int n)
{
	t_redirect	*redirection;

	redirection = tmp;
	while (redirection)
	{
		if ((n == 0 || n == 1) && (redirection->flag == 0
				|| redirection->flag == 1))
			return (1);
		if ((n == 2 || n == 3) && (redirection->flag == 2
				|| redirection->flag == 3))
			return (1);
		redirection = redirection->next;
	}
	return (0);
}

int	ft_open_files(t_node *list, int *files_2, int *files_3)
{
	t_redirect	*redirection;

	redirection = list->command->redirection;
	while (redirection)
	{
		if (redirection->flag == 0 || redirection->flag == 1)
		{
			if (ft_open_input_files(list, files_2, redirection) == FAIL)
				return (FAIL);
		}
		else if (redirection->flag == 2)
		{
			if (ft_open_output_files(list, files_3, redirection) == FAIL)
				return (FAIL);
		}
		else if (redirection->flag == 3)
		{
			if (ft_open_append_files(list, files_3, redirection) == FAIL)
				return (FAIL);
		}
		redirection = redirection->next;
	}
	return (SUCCESS);
}

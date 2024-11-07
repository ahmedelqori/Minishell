/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:39:33 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/31 17:02:28 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_built_in(char *s)
{
	char	*built[8];
	int		i;

	built[0] = "export";
	built[1] = "cd";
	built[2] = "echo";
	built[3] = "env";
	built[4] = "unset";
	built[5] = "exit";
	built[6] = "pwd";
	built[7] = NULL;
	i = 0;
	while (built[i])
	{
		if (ft_strcmp_2(s, built[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_len_env(t_hold *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	ft_open_input_files(t_node *list, int *files_2, t_redirect *redirection)
{
	int	fd;

	fd = open(redirection->str, O_RDONLY);
	if (fd == -1)
	{
		perror(redirection->str);
		list->exit_nb = 1;
		return (FAIL);
	}
	if (ft_is_any_file(redirection->next, redirection->flag))
		close(fd);
	else
		*files_2 = fd;
	return (SUCCESS);
}

int	ft_open_output_files(t_node *list, int *files_3, t_redirect *redirection)
{
	int	fd;

	fd = open(redirection->str, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		perror(redirection->str);
		list->exit_nb = 1;
		return (FAIL);
	}
	if (ft_is_any_file(redirection->next, redirection->flag))
		close(fd);
	else
		*files_3 = fd;
	return (SUCCESS);
}

int	ft_open_append_files(t_node *list, int *files_3, t_redirect *redirection)
{
	int	fd;

	fd = open(redirection->str, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror(redirection->str);
		list->exit_nb = 1;
		return (FAIL);
	}
	if (ft_is_any_file(redirection->next, redirection->flag))
		close(fd);
	else
		*files_3 = fd;
	return (SUCCESS);
}

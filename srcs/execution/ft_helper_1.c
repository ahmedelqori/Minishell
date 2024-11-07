/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:27:55 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/21 14:41:04 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_initialize_files(int *files)
{
	files[0] = dup(STDIN_FILENO);
	if (files[0] == FAIL)
		return (FAIL);
	files[1] = dup(STDOUT_FILENO);
	if (files[1] == FAIL)
	{
		close(files[0]);
		return (FAIL);
	}
	files[2] = files[0];
	files[3] = files[1];
	return (SUCCESS);
}

void	ft_close_all_files(int *fd, int *files)
{
	close(fd[0]);
	close(fd[1]);
	close(files[0]);
	close(files[1]);
	close(files[2]);
	close(files[3]);
}

int	ft_duplicated_uno(int *fd, int *files)
{
	if (files[0] != files[2])
	{
		if (dup2(files[0], STDIN_FILENO) == FAIL)
		{
			ft_close_all_files(fd, files);
			perror(BOLDRED "DUP==" RESET);
			return (FAIL);
		}
	}
	if (files[1] != files[3])
	{
		if (dup2(files[1], STDOUT_FILENO) == FAIL)
		{
			perror("DUP");
			ft_close_all_files(fd, files);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

void	ft_handle_builtin(t_hold **env, t_node *node, t_command *command,
		int *fd)
{
	int	files[4];

	if (ft_initialize_files(files) == FAIL)
		return ;
	if (ft_open_files(node, &files[0], &files[1]) == FAIL)
	{
		ft_close_all_files(fd, files);
		return ;
	}
	if (ft_duplicated_uno(fd, files) == FAIL)
		return ;
	ft_handle_builtin_2(env, node, command);
}

void	ft_wait_all_child_process(t_node *list)
{
	pid_t	all_process;
	int		status;

	while (1)
	{
		all_process = wait(&status);
		if (all_process < 0)
			break ;
		if (all_process == list->last)
			list->exit_nb = WEXITSTATUS(status);
	}
}

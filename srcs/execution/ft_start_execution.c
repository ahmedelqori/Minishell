/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:32:05 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/27 21:08:39 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_handle_signal_child_2(int sig)
{
	int	*p;

	p = ft_global_exit_status();
	if (sig != SIGINT)
		return ;
	write(1, "\n", 1);
	*p = 1;
}

void	ft_after_fork_parent(t_node *list, int *fd, int *files)
{
	signal(SIGINT, ft_handle_signal_child_2);
	if (list->command->next)
	{
		if (dup2(fd[0], STDIN_FILENO) == FAIL)
		{
			perror("DUP");
			return ;
		}
	}
	ft_close_all_files(fd, files);
}

void	ft_after_fork_child(t_node *list, int *fd, int *files, t_hold **env)
{
	signal(SIGINT, SIG_DFL);
	ft_handle_child(list, files, fd, env);
}

void	ft_fork_and_handle_child(t_node *list, int *fd, t_hold **env,
		int *files)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		ft_close_all_files(fd, files);
		perror(BOLDRED "FORK" RESET);
		return ;
	}
	if (list->command->next == NULL)
		list->last = pid;
	if (files[0] != files[2])
	{
		if (dup2(files[0], STDIN_FILENO) == FAIL)
		{
			ft_close_all_files(fd, files);
			perror(BOLDRED "DUP" RESET);
			return ;
		}
	}
	if (pid == 0)
		ft_after_fork_child(list, fd, files, env);
	else
		ft_after_fork_parent(list, fd, files);
}

void	ft_start_execution(t_node *list, int *fd, t_hold **env)
{
	int	files[4];

	if (ft_initialize_files(files) == FAIL)
		return ;
	if (ft_open_files(list, &files[0], &files[1]) == FAIL)
	{
		if (list->command->next)
		{
			if (dup2(fd[0], STDIN_FILENO) == FAIL)
			{
				perror("DUP");
				ft_close_all_files(fd, files);
			}
		}
		ft_close_all_files(fd, files);
		return ;
	}
	ft_fork_and_handle_child(list, fd, env, files);
}

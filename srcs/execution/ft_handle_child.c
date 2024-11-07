/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:04:00 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/01 00:24:16 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_handle_builtin_2(t_hold **env, t_node *node, t_command *command)
{
	void	(*handlers[8])(t_command *, t_hold **, t_node *);

	handlers[0] = handle_export;
	handlers[1] = handle_cd;
	handlers[2] = handle_echo;
	handlers[3] = handle_env;
	handlers[4] = handle_unset;
	handlers[5] = handle_exit;
	handlers[6] = handle_pwd;
	handlers[7] = NULL;
	handlers[is_built_in(command->options[0])](command, env, node);
}

static void	ft_run_builtin(t_hold **env, t_node *list)
{
	if (is_built_in(list->command->options[0]) >= 0
		&& is_built_in(list->command->options[0]) < 7)
	{
		ft_handle_builtin_2(env, list, list->command);
		exit(list->exit_nb);
	}
}

static int	ft_help_child(t_node *list, int *files, int *fd)
{
	if (list->command->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("DUP");
			ft_close_all_files(fd, files);
			return (FAIL);
		}
	}
	if (files[1] != files[3])
	{
		if (dup2(files[1], STDOUT_FILENO) == -1)
		{
			perror("DUP");
			ft_close_all_files(fd, files);
			return (FAIL);
		}
	}
	return (SUCCESS);
}

void	ft_handle_child(t_node *list, int *files, int *fd, t_hold **env)
{
	char	*command;
	char	**arr;

	if (ft_help_child(list, files, fd) == FAIL)
		exit(1);
	ft_close_all_files(fd, files);
	ft_run_builtin(env, list);
	if (list->command->options[0] == NULL)
		exit(0);
	arr = ft_creat_env_arr(*env);
	command = ft_get_right_path(*env, list->command->options[0]);
	if (command == NULL)
	{
		command = list->command->options[0];
		ft_handle_erros(command, list->command->options, arr, *env);
	}
	if (execve(command, list->command->options, arr) < 0)
	{
		perror(list->command->options[0]);
		if (errno == ENOTDIR)
			exit(126);
		exit(127);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 06:29:31 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/11 15:10:58 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	ft_strcmp_2(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

void	ft_check_is_directory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == FAIL)
		return ;
	if (S_ISDIR(file_stat.st_mode) && ft_strchr(path, 47) == SUCCESS)
	{
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": Is a directory\n",
			ft_strlen(": Is a directory\n"));
		exit(126);
	}
}

void	ft_putstr_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, COMMAND_NOT_FOUND, ft_strlen(COMMAND_NOT_FOUND));
}

void	ft_handle_erros(char *command, char **args, char **arr, t_hold *env)
{
	(void)args;
	(void)env;
	(void)arr;
	ft_check_is_directory(command);
	if (access(command, F_OK) != -1 && access(command, X_OK) == -1
		&& ft_strchr(command, '/') == FAIL)
		ft_print_error_and_exit(command, 127);
	if (access(command, F_OK) != -1 && access(command, X_OK) == -1
		&& ft_strchr(command, '/') == SUCCESS)
	{
		perror(command);
		exit(126);
	}
	if (ft_strchr(command, '/') == FAIL && ft_search_env(env) == FAIL
		&& access(command, F_OK & X_OK) != -1)
	{
		if (execve(command, args, arr) == -1)
		{
			perror(args[0]);
			exit(127);
		}
	}
	if (ft_strchr(command, '/') == FAIL)
		ft_print_error_and_exit(command, 127);
}

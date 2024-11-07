/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:20:52 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/26 22:20:18 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_search_env(t_hold *tmp)
{
	while (tmp)
	{
		if (ft_strcmp_2(tmp->key, "PATH"))
			return (SUCCESS);
		tmp = tmp->next;
	}
	return (FAIL);
}

void	ft_print_error_and_exit(char *command, int nb)
{
	ft_putstr_error(command);
	exit(nb);
}

char	*ft_free_and_return(char **arr, char *s)
{
	ft_free_array_1(arr);
	return (s);
}

void	ft_dup_and_close(int org_stdin, int org_stdout)
{
	if (dup2(org_stdin, STDIN_FILENO) == FAIL)
	{
		perror("DUP");
		close(org_stdin);
		close(org_stdout);
		return ;
	}
	if (dup2(org_stdout, STDOUT_FILENO) == FAIL)
	{
		perror("DUP");
		close(org_stdin);
		close(org_stdout);
		return ;
	}
	close(org_stdin);
	close(org_stdout);
	return ;
}

void	ft_start(t_node *cur, int *fd, t_hold **env, char c)
{
	if (cur->command && cur->command->next == NULL
		&& is_built_in(cur->command->options[0]) >= 0
		&& is_built_in(cur->command->options[0]) < 7 && c != 'r')
		ft_handle_builtin(env, cur, cur->command, fd);
	else
	{
		while (cur->command)
		{
			if (cur->command->syntax == 'r')
			{
				cur->command = cur->command->next;
				continue ;
			}
			if (pipe(fd) == FAIL)
			{
				perror("PIPE");
				break ;
			}
			ft_start_execution(cur, fd, env);
			cur->command = cur->command->next;
		}
	}
}

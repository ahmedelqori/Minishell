/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:19:37 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:05:40 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_duplicated_std(int *org_stdin, int *org_stdout, t_command *tmp)
{
	*org_stdin = dup(STDIN_FILENO);
	if (*org_stdin == FAIL)
	{
		perror("dup:\t");
		ft_delete_all_here_doc(tmp);
		return (FAIL);
	}
	*org_stdout = dup(STDOUT_FILENO);
	if (*org_stdin == FAIL)
	{
		perror("dup:\t");
		ft_delete_all_here_doc(tmp);
		close(*org_stdin);
		return (FAIL);
	}
	return (SUCCESS);
}

void	ft_execution(t_node *list, t_hold **env, char c)
{
	int			fd[2];
	int			org_stdin;
	int			org_stdout;
	t_command	*tmp;
	t_node		*cur;

	cur = list;
	if (ft_handle_heredoc(cur, *env) == FAIL)
		return ;
	tmp = cur->command;
	if (ft_duplicated_std(&org_stdin, &org_stdout, tmp) == FAIL)
		return ;
	ft_start(cur, fd, env, c);
	ft_dup_and_close(org_stdin, org_stdout);
	ft_wait_all_child_process(list);
	ft_delete_all_here_doc(tmp);
}

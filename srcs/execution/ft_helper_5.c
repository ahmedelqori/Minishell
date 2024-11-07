/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:21:10 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:20:36 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dup_close_wait(int org_stdin, int org_stdout, t_node *list,
		t_command *tmp)
{
	if (dup2(org_stdin, STDIN_FILENO) == FAIL)
	{
		perror("DUP");
		return ;
	}
	if (dup2(org_stdout, STDOUT_FILENO) == FAIL)
	{
		perror("DUP");
		return ;
	}
	close(org_stdin);
	close(org_stdout);
	ft_wait_all_child_process(list);
	ft_delete_all_here_doc(tmp);
}

void	ft_handle_start_execution(t_node **list, int *fd, t_hold **env)
{
	while ((*list)->command)
	{
		if (pipe(fd) == -1)
		{
			perror("PIPE");
			break ;
		}
		ft_start_execution((*list), fd, env);
		(*list)->command = (*list)->command->next;
	}
}

void	ft_open_random_file(int *id)
{
	int	fd;

	fd = open("/dev/random", O_RDONLY, 0777);
	if (fd == -1)
	{
		printf(BOLDRED "Error" RESET ": open /dev/random");
		*id = -1;
		return ;
	}
	*id = fd;
}

char	*ft_get_unique_file(void)
{
	char	s[11];
	char	*arr;
	int		fd;
	int		i;
	int		n;

	ft_open_random_file(&fd);
	if (fd == -1)
		return (NULL);
	read(fd, s, 10);
	s[10] = 0;
	arr = "0123456789abcdef";
	i = 0;
	while (i < 10)
	{
		if (s[i] < 0)
			s[i] *= -1;
		s[i] = s[i] % 16;
		n = s[i];
		s[i++] = arr[n];
	}
	close(fd);
	return (ft_strdup(s));
}

void	ft_free_array_1(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}

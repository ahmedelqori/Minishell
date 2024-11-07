/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:48:18 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/31 17:26:39 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp_1(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

static void	ft_readline_heredoc(int fd, t_redirect *input, t_hold *env,
		t_node *list)
{
	char	*str;
	int		expand;

	expand = 1;
	if (has_quote(input->str))
		expand = 0;
	input->str = copy_str(input->str);
	while (1)
	{
		str = readline(BOLDYELLOW HERE_DOC RESET);
		if (str == NULL)
			break ;
		if (ft_strcmp_1(str, input->str) == 0)
		{
			free(str);
			break ;
		}
		if (expand)
			str = expand_line(str, env, list);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

void	ft_handle_signal_child(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

char	*ft_creat_herdoc_and_open(int *fd, t_redirect *input)
{
	char	*name;
	char	*full_path;

	name = ft_get_unique_file();
	if (name == NULL)
		return (NULL);
	full_path = ft_strjoin_1(TMP_FILE, name);
	*fd = open(full_path, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	free(name);
	if (*fd == -1)
	{
		free(input->str);
		input->str = full_path;
		perror("HereDoc");
		return (NULL);
	}
	return (full_path);
}

int	ft_help_here_doc(t_node *list, t_hold *env, t_redirect *input)
{
	char	*full_path;
	int		status;
	int		fd;
	int		pid;

	full_path = ft_creat_herdoc_and_open(&fd, input);
	if (full_path == NULL)
		return (FAIL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_handle_signal_child);
		ft_readline_heredoc(fd, input, env, list);
		exit(0);
	}
	wait(&status);
	list->exit_nb = WEXITSTATUS(status);
	free(input->str);
	input->str = full_path;
	close(fd);
	if (list->exit_nb != 0)
		return (FAIL);
	return (SUCCESS);
}

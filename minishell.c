/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:42:38 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/01 12:21:28 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*check_input(char *s, t_hold **env, t_node *node)
{
	int	*p;

	p = ft_global_exit_status();
	s = readline(BOLDGREEN "Minishell > " RESET);
	if (!s)
	{
		free_env(env);
		if (*p == 1)
			exit(130);
		exit(node->exit_nb);
	}
	return (s);
}

void	parse_input(char *s, t_node *node, t_hold **env)
{
	char		*c;
	t_command	*current;

	c = ft_global_syntax_check();
	parsing(node, s, *env);
	split_parsing(node, s);
	current = node->command;
	if (*c != 's')
		ft_execution(node, env, *c);
	change_variable(env, current);
	free_command(&current);
	node->command = NULL;
	free(s);
}

char	*bash_helper(char *s, t_node *node, char *temp)
{
	int	*n;

	if (*s)
		add_history(temp);
	free(temp);
	n = ft_global_exit_status();
	if (*n == 1)
	{
		node->exit_nb = 130;
		*n = 0;
	}
	ft_add_command(&node->command, ft_new_command());
	return (s);
}

void	run_bash(t_node *node, t_hold **env, char *s)
{
	char	*temp;

	while (1)
	{
		ft_signals();
		s = check_input(s, env, node);
		temp = ft_strdup(s);
		s = ft_strtrim(s, " ");
		s = bash_helper(s, node, temp);
		if (!*s)
		{
			free_command(&node->command);
			free(s);
			continue ;
		}
		parse_input(s, node, env);
		print_error(node);
	}
}

int	main(int ac, char **av, char **envr)
{
	t_node	node;
	t_hold	*env;
	char	*s;

	(void)ac;
	(void)**av;
	s = NULL;
	env = NULL;
	ft_new_node(&node);
	initialize_env(&env, envr);
	ft_put_env_arr_2(env);
	run_bash(&node, &env, s);
}

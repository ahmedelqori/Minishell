/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:28 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:24:28 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*copy_data(char **str)
{
	char	*x;
	char	*temp;
	char	*buffer;

	buffer = ft_calloc(2048);
	x = *str;
	temp = buffer;
	while (*x == ' ' || *x == '\t')
		x++;
	while (*x != '|' && *x != '<' && *x != '>' && *x != ' ' && *x != '\t' && *x)
	{
		if (*x == '"' || *x == '\'')
			parsing_quote(&temp, &x);
		else if (*x != '|' && *x != '<' && *x != '>' && *x != ' ' && *x != '\t'
			&& *x)
			*temp++ = *x++;
	}
	*str = x;
	return (buffer);
}

void	parsing_input(t_node *content, char **str, t_hold *env)
{
	char	*x;
	char	*buffer;
	int		flag;

	x = *str;
	flag = 0;
	x++;
	if (*x == '<')
	{
		flag++;
		x++;
	}
	buffer = copy_data(&x);
	if (*x == '|' || *x == '<' || *x == '>' || *x == ' ' || *x == '\t' || !*x)
		buffer = expand_redirection(content, buffer, flag, env);
	while (*x == ' ' || *x == '\t')
		x++;
	free(buffer);
	*str = x;
}

void	parsing_output(t_node *content, char **str, t_hold *env)
{
	char	*x;
	char	*buffer;
	int		flag;

	x = *str;
	flag = 2;
	x++;
	if (*x == '>')
	{
		flag++;
		x++;
	}
	buffer = copy_data(&x);
	if (*x == '|' || *x == '<' || *x == '>' || *x == ' ' || *x == '\t' || !*x)
		buffer = expand_redirection(content, buffer, flag, env);
	while (*x == ' ' || *x == '\t')
		x++;
	free(buffer);
	*str = x;
}

void	parsing_standard(t_node *content, char **str, t_hold *env)
{
	char	*x;
	char	*buffer;

	x = *str;
	buffer = copy_data(&x);
	if (*x == '|' || *x == '<' || *x == '>' || *x == ' ' || *x == '\t' || !*x)
		buffer = expand_command(content, buffer, env);
	while (*x == ' ' || *x == '\t')
		x++;
	if (*x == '|')
	{
		ft_add_command(&content->command, ft_new_command());
		if (*x == '|')
			x++;
	}
	free(buffer);
	*str = x;
}

void	parsing(t_node *content, char *str, t_hold *env)
{
	if (!str || !*str)
		return ;
	if (*str == '<')
		parsing_input(content, &str, env);
	else if (*str == '>')
		parsing_output(content, &str, env);
	else
		parsing_standard(content, &str, env);
	parsing(content, str, env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:42 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:35:34 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_var(char *str, t_hold *env, char *s2, int i)
{
	t_hold	*current;
	char	*k;
	int		l;

	current = env;
	l = 0;
	while (current)
	{
		if (ft_strcmp_2(current->key, str))
		{
			k = ft_strdup(current->value);
			if (!k)
				return (-1);
			while (k[l])
				s2[i++] = k[l++];
			free(k);
			return (i);
		}
		current = current->next;
	}
	return (-1);
}

int	help_quote(char *s, int i)
{
	char	c;

	c = s[i++];
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	i++;
	return (i);
}

int	split_command(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (help_quote(s, i) < 0)
				return (0);
			i = help_quote(s, i);
		}
		else if (s[i] == '|')
		{
			if (i == 0)
				return (0);
			i++;
			while (s[i] == ' ' || s[i] == '\t')
				i++;
			if (!s[i] || s[i] == '|')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

void	copy_quote(char **s, char **buffer, t_hold *env, t_node *content)
{
	char	*temp;
	char	c;
	char	*tmp;

	tmp = *buffer;
	temp = *s;
	c = *temp;
	if (c == '"' || c == '\'')
	{
		*tmp++ = *temp++;
		while (*temp && *temp != c)
		{
			if (c == '"' && *temp == '$')
				helper(&temp, &tmp, env, content);
			else if (*temp && *temp != c)
				*tmp++ = *temp++;
		}
		if (*temp)
			*tmp++ = *temp++;
	}
	*buffer = tmp;
	*s = temp;
}

char	*expand_buffer(char *str, t_hold *env, t_node *content)
{
	char	*buffer;
	char	*x;
	char	*temp;

	buffer = ft_calloc(2048);
	temp = buffer;
	x = str;
	while (*x)
	{
		if (*x == '$')
			helper(&x, &temp, env, content);
		else if (*x == '"' || *x == '\'')
			copy_quote(&x, &temp, env, content);
		else if (*x)
			*temp++ = *x++;
	}
	free(str);
	return (buffer);
}

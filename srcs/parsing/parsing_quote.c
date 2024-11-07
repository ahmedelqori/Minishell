/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:23 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 20:31:31 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_quote(char **temp, char **str)
{
	char	*x;
	char	*y;
	int		c;

	x = *temp;
	y = *str;
	c = *y;
	*x++ = *y++;
	while (*y != c && *y)
		*x++ = *y++;
	if (*y)
		*x++ = *y++;
	*temp = x;
	*str = y;
}

int	handle_variable(char **k, char *s2, t_hold *env, int i)
{
	char	*temp;
	char	env_var[2048];
	int		l;

	l = 0;
	temp = *k;
	ft_bzero(env_var, 2048);
	l = 0;
	temp++;
	while (*temp && (is_alpha(*temp) || is_num(*temp)))
		env_var[l++] = *temp++;
	if (check_var(env_var, env, s2, i) >= 0)
		i = check_var(env_var, env, s2, i);
	*k = temp;
	return (i);
}

int	escape_quote(char **s1, char **p1)
{
	char	*p;
	char	*s;
	char	c;

	p = *p1;
	s = *s1;
	if (*p == '"' || *p == '\'')
	{
		c = *p++;
		while (*p && *p != c)
		{
			if (*p == *s)
			{
				s++;
				p++;
			}
			else
				return (0);
		}
		if (*p)
			p++;
	}
	*s1 = s;
	*p1 = p;
	return (1);
}

void	copy_redirection(char **s1, char **s2)
{
	char	*tmp;
	char	*temp;

	temp = *s1;
	tmp = *s2;
	*tmp++ = *temp++;
	while (*temp && *temp != ' ' && *temp != '<' && *temp != '>' && *temp != '|'
		&& *temp != '\t')
	{
		if (*temp == '\'' || *temp == '"')
			parsing_quote(&tmp, &temp);
		else
			*tmp++ = *temp++;
	}
	*s1 = temp;
	*s2 = tmp;
}

void	copy_rest(char **temp, char **tmp, t_hold *env, t_node *content)
{
	char	*s1;
	char	*s2;

	s1 = *temp;
	s2 = *tmp;
	escape_space(&s1, &s2);
	while (*s1 && *s1 != ' ' && *s1 != '<' && *s1 != '>' && *s1 != '\t')
	{
		if (*s1 == '$')
			helper(&s1, &s2, env, content);
		else if (*s1 == '"' || *s1 == '\'')
			copy_quote(&s1, &s2, env, content);
		else if (*s1)
			*s2++ = *s1++;
	}
	*temp = s1;
	*tmp = s2;
}

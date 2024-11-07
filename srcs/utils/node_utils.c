/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relhamma <relhamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:25:18 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:26:14 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_new_node(t_node *new)
{
	new->command = NULL;
	new->exit_nb = 0;
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_num(char c)
{
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

void	*ft_global_syntax_check(void)
{
	static char	c;

	return (&c);
}

char	*find_value(char *str, char *buffer)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	else
		return (NULL);
	while (str[i])
		buffer[k++] = str[i++];
	return (buffer);
}

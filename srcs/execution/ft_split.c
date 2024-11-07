/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:19:59 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/20 20:20:01 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_push_string(const char *s, char c)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*s && *s != c)
	{
		str[i] = *s;
		i++;
		s++;
	}
	str[len] = '\0';
	return (str);
}

static char	**ft_free_array(char **tab, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_count_word(s, c);
	tab = malloc((len + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		tab[i] = ft_push_string(s, c);
		if (tab[i] == NULL)
			return (ft_free_array(tab, i));
		s += ft_strlen(tab[i]);
		i++;
	}
	tab[len] = 0;
	return (tab);
}

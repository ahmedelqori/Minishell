/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:18:38 by ael-qori          #+#    #+#             */
/*   Updated: 2024/04/01 12:23:51 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_put_env_arr(t_hold *t, int j, char **arr)
{
	char	*tmp;

	if (!t)
		return ;
	tmp = ft_strjoin_1("=", t->value);
	arr[j] = ft_strjoin_1(t->key, tmp);
	free(tmp);
}

char	**ft_creat_env_arr(t_hold *env)
{
	t_hold	*t;
	char	**arr;
	int		i;
	int		j;

	j = 0;
	i = ft_len_env(env);
	arr = malloc(sizeof(char *) * (i + 1));
	if (arr == NULL)
		return (NULL);
	t = env;
	while (j < i)
	{
		ft_put_env_arr(t, j, arr);
		j++;
		t = t->next;
	}
	arr[j] = NULL;
	return (arr);
}

static char	**ft_help_get_right_path(t_hold *tmp)
{
	char	**arr;

	arr = NULL;
	while (tmp)
	{
		if (ft_strcmp_2(tmp->key, "PATH"))
		{
			if (tmp->value)
			{
				arr = ft_split(tmp->value, ':');
				return (arr);
			}
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_right_path(t_hold *env, char *command)
{
	t_hold	*tmp;
	char	*str;
	char	*tmp_ptr;
	char	**arr;
	int		i;

	if (ft_strchr(command, '/') == SUCCESS)
		return (NULL);
	i = 0;
	tmp = env;
	if (ft_strlen(command) == 0)
		return (NULL);
	arr = ft_help_get_right_path(tmp);
	if (arr == NULL)
		return (NULL);
	while (arr[i])
	{
		tmp_ptr = ft_strjoin_1(arr[i++], "/");
		str = ft_strjoin_1(tmp_ptr, command);
		free(tmp_ptr);
		if (access(str, F_OK & X_OK) != -1)
			return (ft_free_and_return(arr, str));
		free(str);
	}
	return (ft_free_and_return(arr, NULL));
}

char	*ft_strjoin_1(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s2));
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (*s1)
		while (*s1)
			str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = 0;
	return (str);
}

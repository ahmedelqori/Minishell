/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:24:52 by ael-qori          #+#    #+#             */
/*   Updated: 2024/03/25 21:23:44 by relhamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_global_exit_status(void)
{
	static int	p = 0;

	return (&p);
}

void	ft_handle_sigint(int sig)
{
	int	*p;

	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	p = ft_global_exit_status();
	*p = 1;
}

void	ft_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint);
}

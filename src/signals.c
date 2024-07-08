/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:43:39 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/08 13:46:06 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_sigquit(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

void	heredoc_sigint(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGQUIT, heredoc_sigquit);
	}
}

void	heredoc_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, heredoc_sigint);
	// signal(SIGQUIT, handle_sigquit);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
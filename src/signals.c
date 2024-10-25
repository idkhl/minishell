/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:43:39 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/25 19:41:08 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_signal;

void	heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
	}
}

void	exec_signals(int sig)
{
	if (sig == SIGINT)
	{
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dump)");
	}
}

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//parent:	^C -> ^C + newline
//			^D -> exit
//			^\ -> rien
//enfant:	^C -> ^C + newline
//			^D -> newline
//			^\ -> ^\Quit (core dumped)
//heredoc:	^C -> ^C + newline
//			^D -> warning: ... + newline
//			^\ -> rien
// mettre exit pour ctr D
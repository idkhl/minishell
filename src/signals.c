/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:43:39 by idakhlao          #+#    #+#             */
/*   Updated: 2024/11/01 19:49:19 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
			return ;
		g_signal = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	exec_signals(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
	}
	if (sig == SIGQUIT)
	{
		g_signal = 131;
		ft_putendl_fd("Quit (core dump)", 2);
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
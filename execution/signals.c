/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:59 by achater           #+#    #+#             */
/*   Updated: 2024/08/05 22:00:38 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_signals(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_orig_int;

	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ignore, &sa_orig_int);
	sigaction(SIGQUIT, &sa_ignore, &sa_orig_int);
}

void	setup_signal_handlers(void (*int_)(int), void (*quit_)(int))
{
	rl_catch_signals = 1;
	signal(SIGINT, int_);
	signal(SIGQUIT, quit_);
}

void	sig_handler_child(int sig)
{
	extern int	g_caught;

	if (sig == SIGINT)
	{
		g_status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit(131);
	}
}

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		exit(1);
	}
}

void	handle_sigint(int signum)
{
	extern int	g_status;
	if (signum == SIGINT)
	{
		exit_status(1);
		g_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

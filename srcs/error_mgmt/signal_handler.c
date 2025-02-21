/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:06:18 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/06 16:20:57 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit_process(int signum)
{
	(void)signum;
	if (printf("Quit (core dunmp)\n") < 0)
		return (perror("printf"));
	g_exit_status = 131;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint_process(int signal)
{
	(void)signal;
	if (printf("\n") < 0)
		return (perror("printf"));
	g_exit_status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	if (printf("\n") < 0)
		return (perror("printf"));
	g_exit_status = 130;
	rl_replace_line("", 0);
	if (close(STDIN_FILENO) == -1)
		perror("close");
}

void	sigint_handler(int signal)
{
	(void)signal;
	if (printf("\n") < 0)
		return (perror("printf"));
	g_exit_status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal_action(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, &handle_sigint_process);
		signal(SIGQUIT, &handle_sigquit_process);
	}
	if (mode == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_sigint_heredoc);
	}
}

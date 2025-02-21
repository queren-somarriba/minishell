/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:18:12 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 17:21:06 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_process(t_minishell *data, t_cmd *cmd, int *pipefd, pid_t pid)
{
	pid_t	endpid;
	int		status;
	t_list	*last;

	last = lstlast_cmd(*data->tkn_lst);
	if (close(pipefd[1]) == -1)
		return (perror("close"), EXIT_FAILURE);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		return (close(pipefd[0]), perror ("dup2"), EXIT_FAILURE);
	if (close(pipefd[0]) == -1)
		return (perror("close"), EXIT_FAILURE);
	if (last && cmd == (t_cmd *)last->content)
	{
		while (1)
		{
			endpid = waitpid(-1, &status, 0);
			if (endpid == pid)
				if (WIFEXITED(status))
					g_exit_status = WEXITSTATUS(status);
			if (endpid == -1)
				break ;
		}
	}
	return (EXIT_SUCCESS);
}

int	run_cmds(t_cmd *cmd, t_minishell *data)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (!pid)
	{
		g_exit_status = child_process(data, cmd, pipefd);
		free_minishell (data);
		exit(g_exit_status);
	}
	if (pid > 0)
	{
		if (parent_process(data, cmd, pipefd, pid) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	run_node(t_minishell *data, t_list *node)
{
	t_cmd	*cmd;
	t_list	*last;
	int		res;

	res = EXIT_SUCCESS;
	cmd = (t_cmd *)node->content;
	last = lstlast_cmd(*data->tkn_lst);
	if (cmd->token == CMD)
	{
		if (run_cmds(cmd, data) == EXIT_FAILURE)
			res = EXIT_FAILURE;
	}
	if (node == last)
	{
		if (restore_stds(data))
			return (EXIT_FAILURE);
	}
	return (res);
}

int	x_pipe(t_minishell *data)
{
	t_list	*tmp;
	int		res;

	tmp = *data->tkn_lst;
	set_signal_action(1);
	if (dup_stds(data))
		return (EXIT_FAILURE);
	while (tmp)
	{
		res = run_node(data, tmp);
		tmp = tmp->next;
	}
	set_signal_action(0);
	return (res);
}

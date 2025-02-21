/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:49:06 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 17:25:34 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_child(t_minishell *data, t_cmd *cmd, t_list *last, int *pipefd)
{
	if (close(pipefd[0]) == -1)
		return (perror ("close"), close(pipefd[1]),
			close_stds(data), EXIT_FAILURE);
	if (close_stds(data))
		return (close(pipefd[1]), EXIT_FAILURE);
	if (last && cmd != (t_cmd *)last->content)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), close(pipefd[1]), EXIT_FAILURE);
	}
	if (close(pipefd[1]) == -1)
		return (perror("close"), EXIT_FAILURE);
	if (x_redir_lst(cmd->redir_lst))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	close_redir(t_list *lst)
{
	t_cmd	*cmd;

	if (!lst)
		return (EXIT_SUCCESS);
	cmd = (t_cmd *)lst->content;
	while (lst)
	{
		if (cmd->token > 0 && cmd->token < 5)
		{
			if (cmd->redir->fd > 0)
			{
				if (close(cmd->redir->fd) == -1)
					return (perror("close"), EXIT_FAILURE);
			}
			cmd->redir->fd = -1;
		}
		lst = lst->next;
		if (lst)
			cmd = (t_cmd *)lst->content;
	}
	return (EXIT_SUCCESS);
}

int	child_process(t_minishell *data, t_cmd *cmd, int *pipefd)
{
	int		res;
	t_list	*last;

	last = lstlast_cmd(*data->tkn_lst);
	res = 0;
	if (setup_child(data, cmd, last, pipefd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (close_redir(*data->tkn_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (cmd->cmd_arr && is_builtin(cmd->cmd_arr[0]))
	{
		signal(SIGPIPE, SIG_IGN);
		res = exec_builtin(cmd, data);
		return (res);
	}
	else if (cmd->cmd_arr)
	{
		res = x_cmd(cmd->cmd_arr, data->env, data);
		if (res != EXIT_SUCCESS)
			exit(res);
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:39:35 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 18:24:08 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	x_redir_lst(t_list **lst)
{
	t_list	*tmp;
	t_cmd	*cmd_node;

	tmp = NULL;
	if (lst)
		tmp = *lst;
	while (tmp)
	{
		cmd_node = (t_cmd *)tmp->content;
		if (cmd_node->token > 0 && cmd_node->token < 5)
		{
			if (parse_redirection(cmd_node->redir))
				return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	dup_stds(t_minishell *data)
{
	data->stdin = dup(STDIN_FILENO);
	if (data->stdin == -1)
		return (perror("dup"), EXIT_FAILURE);
	data->stdout = dup(STDOUT_FILENO);
	if (data->stdout == -1)
		return (perror("dup"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	restore_stds(t_minishell *data)
{
	if (dup2(data->stdin, STDIN_FILENO) == -1)
		return (close(data->stdin), close (data->stdout),
			perror("dup2"), EXIT_FAILURE);
	if (close(data->stdin) == -1)
		return (perror("close"), close(data->stdout), EXIT_FAILURE);
	data->stdin = -1;
	if (dup2(data->stdout, STDOUT_FILENO) == -1)
		return (close (data->stdout), perror("dup2"), EXIT_FAILURE);
	if (close(data->stdout) == -1)
		return (perror("close"), EXIT_FAILURE);
	data->stdout = -1;
	return (EXIT_SUCCESS);
}

int	close_stds(t_minishell *data)
{
	if (data->stdin != -1)
	{
		if (close(data->stdin) == -1)
			return (perror("close"), EXIT_FAILURE);
		data->stdin = -1;
	}
	if (data->stdout != -1)
	{
		if (close(data->stdout) == -1)
			return (perror("close"), EXIT_FAILURE);
		data->stdout = -1;
	}
	return (EXIT_SUCCESS);
}

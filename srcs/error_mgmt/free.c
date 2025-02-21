/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:22:39 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/14 18:54:34 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_lst(t_list **lst)
{
	t_list	*current;
	t_list	*tmp;

	if (lst)
	{
		if (*lst)
		{
			current = *lst;
			while (current)
			{
				tmp = current;
				current = current->next;
				free(tmp);
			}
			*lst = NULL;
		}
		free(lst);
		lst = NULL;
	}
}

void	free_tkn_node(t_list *node)
{
	t_cmd			*tmp_cmd;

	tmp_cmd = (t_cmd *)node->content;
	if (tmp_cmd->tkn_str)
		free(tmp_cmd->tkn_str);
	if (tmp_cmd->token > 0 && tmp_cmd->token < 5 && tmp_cmd->redir)
	{
		free(tmp_cmd->redir->target);
		if (tmp_cmd->redir->fd > 0)
		{
			if (close(tmp_cmd->redir->fd) == -1)
				return (perror("close"));
		}
		free(tmp_cmd->redir);
	}
	if (tmp_cmd->token == CMD && tmp_cmd->cmd_arr)
		ft_free_array(tmp_cmd->cmd_arr);
	if (tmp_cmd->token == CMD && tmp_cmd->redir_lst)
		free_redir_lst(tmp_cmd->redir_lst);
	free(node->content);
	free(node);
}

void	free_tkn_lst(t_list **tkn_lst)
{
	t_list			*tmp;

	tmp = NULL;
	if (tkn_lst)
	{
		if (*tkn_lst)
		{
			while (*tkn_lst)
			{
				tmp = *tkn_lst;
				*tkn_lst = (*tkn_lst)->next;
				free_tkn_node(tmp);
			}
			free(*tkn_lst);
		}
		free(tkn_lst);
	}
}

void	free_minishell(t_minishell *data)
{
	if (data->env)
		ft_free_array(data->env);
	if (data->cmd_line)
		free(data->cmd_line);
	if (data->tkn_lst)
		free_tkn_lst(data->tkn_lst);
	rl_clear_history();
}

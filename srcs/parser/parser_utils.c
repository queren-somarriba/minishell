/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:12:18 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 19:24:03 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_redir(t_minishell *data, t_cmd *node, t_cmd *next, t_list **redir_lst)
{
	node->redir = malloc(sizeof(t_redir));
	if (!node->redir)
		return (perror("malloc"), EXIT_FAILURE);
	if (node->token == HERE_DOC)
		node->redir->target = expand(data, next->tkn_str, 0);
	else
		node->redir->target = expand(data, next->tkn_str, 1);
	if (!node->redir->target)
		return (perror("malloc"), free(node->redir), 1);
	node->redir->type = node->token;
	node->redir->fd = -1;
	if (node->redir->type == HERE_DOC)
		node->redir->fd = heredoc_manage(
				node->redir->target, data, redir_lst);
	return (EXIT_SUCCESS);
}

static int	fillup_cmd_arr(t_minishell *data, t_list *tkn_node, t_cmd *node)
{
	t_cmd	*next_node;
	size_t	i;

	i = -1;
	next_node = NULL;
	if (tkn_node->next)
		next_node = (t_cmd *)tkn_node->next->content;
	node->cmd_arr[++i] = expand(data, node->tkn_str, 1);
	if (!node->cmd_arr[i])
		return (perror("malloc"), EXIT_FAILURE);
	while (next_node && next_node->token != PIPE)
	{
		if (next_node->token == CMD_ARG)
		{
			node->cmd_arr[++i] = expand(data, next_node->tkn_str, 1);
			if (!node->cmd_arr[i])
				return (perror("malloc"), ft_free_array(node->cmd_arr), 1);
		}
		tkn_node = tkn_node->next;
		next_node = NULL;
		if (tkn_node->next)
			next_node = (t_cmd *)tkn_node->next->content;
	}
	node->cmd_arr[++i] = NULL;
	return (EXIT_SUCCESS);
}

static int	make_cmd_arr(t_minishell *data, t_list *tkn_node)
{
	t_cmd	*current_node;

	current_node = (t_cmd *)tkn_node->content;
	if (!current_node->tkn_str)
	{
		current_node->cmd_arr = NULL;
		return (EXIT_SUCCESS);
	}
	current_node->cmd_arr = malloc(sizeof(char *)
			* (count_arg_nbr(tkn_node) + 2));
	if (!current_node->cmd_arr)
		return (perror("malloc"), EXIT_FAILURE);
	if (fillup_cmd_arr(data, tkn_node, current_node) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	fillup_cmd_node(t_minishell *data, t_list *tkn_node, t_list **redir_lst)
{
	t_cmd	*current_node;
	t_cmd	*next_node;

	current_node = (t_cmd *)tkn_node->content;
	next_node = NULL;
	if (tkn_node->next)
		next_node = (t_cmd *)tkn_node->next->content;
	if (current_node->token >= 1 && current_node->token <= 4)
		make_redir(data, current_node, next_node, redir_lst);
	if (current_node->token == CMD)
		if (make_cmd_arr(data, tkn_node) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:49:09 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 19:24:07 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_tkn_node(t_minishell *d, t_list **r_lst, t_list *node)
{
	t_cmd	*tkn_node;

	tkn_node = (t_cmd *) node->content;
	if (tkn_node->token < CMD_ARG)
	{
		if (fillup_cmd_node(d, node, r_lst) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (tkn_node->token > 0 && tkn_node->token < 5)
		ft_lstadd_back(r_lst, ft_lstnew(tkn_node));
	return (EXIT_SUCCESS);
}

static	void	add_nocmd_node(t_list *node, t_list **redir_lst, t_list **lst)
{
	t_cmd	*nocmd;
	t_list	*new;

	nocmd = malloc(sizeof (t_cmd));
	if (!nocmd)
		perror("malloc");
	nocmd->token = CMD;
	nocmd->redir = NULL;
	nocmd->redir_lst = redir_lst;
	nocmd->tkn_str = NULL;
	nocmd->cmd_arr = NULL;
	new = ft_lstnew(nocmd);
	if (!new)
		return (perror("malloc"));
	ft_lstadd_before(lst, node, new);
}

t_list	**handle_rlst(t_list *node, t_list **r_lst, t_cmd *last, t_list **lst)
{
	if (((t_cmd *)node->content)->token == PIPE || !node->next)
	{
		if (r_lst && *r_lst == NULL)
		{
			free(r_lst);
			r_lst = NULL;
		}
		if (last)
			last->redir_lst = r_lst;
		else if (r_lst)
			add_nocmd_node(node, r_lst, lst);
		if ((node->next && node->next->next)
			|| (node->next && ((t_cmd *)node->content)->token == PIPE))
		{
			r_lst = malloc(sizeof(t_list *));
			if (!r_lst)
				return (perror("malloc"), NULL);
			*r_lst = NULL;
		}
	}
	return (r_lst);
}

int	parse_tkn_lst(t_list *current, t_list **redir_lst, t_minishell *data)
{
	t_cmd	*last_cmd;

	last_cmd = NULL;
	while (current)
	{
		if (((t_cmd *)current->content)->token == CMD)
			last_cmd = (t_cmd *)current->content;
		if (parse_tkn_node(data, redir_lst, current) == EXIT_FAILURE)
			return (free_redir_lst(redir_lst), EXIT_FAILURE);
		redir_lst = handle_rlst(current, redir_lst, last_cmd, data->tkn_lst);
		if (((t_cmd *)current->content)->token == PIPE)
			last_cmd = NULL;
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	parser(t_minishell *data)
{
	t_list	*current;
	t_list	**redir_lst;

	if (str_is_white_space(data->cmd_line))
		return (EXIT_SUCCESS);
	redir_lst = malloc(sizeof(t_list *));
	if (!redir_lst)
		return (perror("malloc"), EXIT_FAILURE);
	*redir_lst = NULL;
	if (data->tkn_lst)
		current = *data->tkn_lst;
	else
		return (free(redir_lst), EXIT_SUCCESS);
	if (parse_tkn_lst(current, redir_lst, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

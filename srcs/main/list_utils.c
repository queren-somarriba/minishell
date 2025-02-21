/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:32:46 by qsomarri          #+#    #+#             */
/*   Updated: 2025/01/27 18:04:34 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lstlast_cmd(t_list *lst)
{
	t_list	*last;
	t_list	*tmp_lst;
	t_cmd	*tmp_cmd;

	last = NULL;
	tmp_lst = lst;
	while (tmp_lst)
	{
		tmp_cmd = (t_cmd *)tmp_lst->content;
		if (tmp_cmd->token == CMD)
			last = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (last);
}

size_t	lstsize_cmd(t_list *lst)
{
	t_list	*tmp_lst;
	t_cmd	*tmp_cmd;
	size_t	res;

	tmp_lst = lst;
	res = 0;
	while (tmp_lst)
	{
		tmp_cmd = (t_cmd *)tmp_lst->content;
		if (tmp_cmd->token == CMD)
			res++;
		tmp_lst = tmp_lst->next;
	}
	return (res);
}

t_list	*lstfirst_cmd(t_list *lst)
{
	t_list	*tmp_lst;
	t_cmd	*tmp_cmd;

	tmp_lst = lst;
	while (tmp_lst)
	{
		tmp_cmd = (t_cmd *)tmp_lst->content;
		if (tmp_cmd->token == CMD)
			return (tmp_lst);
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}

t_list	*rm_empty_exp(t_list **lst, t_list *node, t_list *prev, t_minishell *d)
{
	char	*tmp;

	tmp = expand(d, ((t_cmd *)node->content)->tkn_str, 0);
	if (tmp[0] == '\0')
	{
		if (node == *lst)
		{
			prev = node->next;
			free_tkn_node(node);
			node = prev;
			*lst = prev;
		}
		else
		{
			prev->next = node->next;
			free_tkn_node(node);
			node = prev->next;
		}
	}
	else
	{
		prev = node;
		node = node->next;
	}
	return (free(tmp), node);
}

void	handle_empty_tkn(t_list **lst, t_minishell *data)
{
	t_list	*node;
	t_list	*prev;

	node = NULL;
	if (lst)
	{
		prev = *lst;
		node = *lst;
	}
	while (node)
	{
		if (((t_cmd *)(node->content))->tkn_str[0] != '\0')
			node = rm_empty_exp(lst, node, prev, data);
		else
		{
			prev = node;
			node = node->next;
		}
	}
}

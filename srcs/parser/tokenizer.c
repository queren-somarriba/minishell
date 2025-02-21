/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:35:21 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 12:13:29 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_token_node(char *str, size_t index)
{
	t_cmd	*tmp_cmd;
	t_list	*new_node;
	size_t	i;

	i = -1;
	tmp_cmd = malloc(sizeof(t_cmd));
	if (!tmp_cmd)
		return (perror("malloc"), NULL);
	tmp_cmd->tkn_str = get_one_token(str, index);
	if (!tmp_cmd->tkn_str)
		return (free(tmp_cmd), NULL);
	tmp_cmd->token = 0;
	tmp_cmd->redir = NULL;
	tmp_cmd->cmd_arr = NULL;
	tmp_cmd->redir_lst = NULL;
	new_node = ft_lstnew(tmp_cmd);
	if (!new_node)
		return (perror("malloc"), free(tmp_cmd->tkn_str),
			free(tmp_cmd), NULL);
	while (tmp_cmd->tkn_str[++i] && !tmp_cmd->token)
	{
		if (is_meta_char(tmp_cmd->tkn_str, i))
			tmp_cmd->token = is_meta_char(tmp_cmd->tkn_str, i);
	}
	return (new_node);
}

static void	set_token_arg_after_cmd(t_list *tmp)
{
	t_cmd	*node;

	tmp = tmp->next;
	node = NULL;
	if (tmp)
		node = (t_cmd *)tmp->content;
	while (node && node->token != PIPE && tmp->next)
	{
		if (node->token == CMD)
			node->token = CMD_ARG;
		tmp = tmp->next;
		node = (t_cmd *)tmp->content;
	}
	if (node && node->token == CMD)
		node->token = CMD_ARG;
}

static void	set_token_arg(t_list **lst)
{
	t_list	*tmp;
	t_cmd	*node;
	t_cmd	*next_cmd;

	tmp = *lst;
	while (tmp)
	{
		node = (t_cmd *)tmp->content;
		next_cmd = NULL;
		if (tmp->next)
			next_cmd = (t_cmd *)tmp->next->content;
		if (node->token != PIPE && node->token != CMD && node->token < CMD_ARG)
		{
			if (next_cmd && (next_cmd->token > PIPE || next_cmd->token == CMD))
				next_cmd->token = TARGET;
		}
		else if (node->token == CMD)
			set_token_arg_after_cmd(tmp);
		tmp = tmp->next;
	}
}

static size_t	add_tkn(t_list **tkn_lst, char *str, size_t index)
{
	t_cmd	*tmp_cmd;
	t_list	*new_node;

	new_node = make_token_node(str, index);
	if (!new_node)
		return (++index);
	ft_lstadd_back(tkn_lst, new_node);
	tmp_cmd = (t_cmd *)new_node->content;
	index += ft_strlen(tmp_cmd->tkn_str);
	return (index);
}

t_list	**tokenizer(char *str)
{
	char	*trim_str;
	size_t	index;
	t_list	**tkn_lst;

	tkn_lst = malloc(sizeof(t_list *));
	if (!tkn_lst)
		return (perror("malloc"), NULL);
	*tkn_lst = NULL;
	index = 0;
	trim_str = ft_strdup(str);
	if (!trim_str)
		return (perror("malloc"), free(tkn_lst), NULL);
	while (str[index])
	{
		index = add_tkn(tkn_lst, str, index);
		free(trim_str);
		trim_str = ft_substr(str, index, ft_strlen(str) - index);
		if (!trim_str)
			return (perror("malloc"), free_tkn_lst(tkn_lst), NULL);
	}
	set_token_arg(tkn_lst);
	if (check_token_lst(tkn_lst) == EXIT_FAILURE)
		return (free(trim_str), free_tkn_lst(tkn_lst), NULL);
	return (free(trim_str), tkn_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:09:14 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/12 15:22:06 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (go_to_nextquote(str, i))
				i += go_to_nextquote(str, i);
			else
				return (exit_status(2),
					error_msg("command is missing a single quote"), 1);
		}
		if (str[i] == '\"')
		{
			if (go_to_nextquote(str, i))
				i += go_to_nextquote(str, i);
			else
				return (exit_status(2),
					error_msg("command is missing a double quote"), 1);
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_syntax_error(t_cmd *current_node, t_cmd *next_node)
{
	if (current_node->token == REDIR_IN && next_node->token != TARGET)
		return (exit_status(2),
			error_msg("syntax error after token '<'"), EXIT_FAILURE);
	if (current_node->token == HERE_DOC && next_node->token != TARGET)
		return (exit_status(2),
			error_msg("syntax error after token '<<'"), EXIT_FAILURE);
	if (current_node->token == REDIR_OUT && next_node->token != TARGET)
		return (exit_status(2),
			error_msg("syntax error after token '>'"), EXIT_FAILURE);
	if (current_node->token == APPEND && next_node->token != TARGET)
		return (exit_status(2),
			error_msg("syntax error after token '>>'"), EXIT_FAILURE);
	if (current_node->token == PIPE && next_node->token == PIPE)
		return (exit_status(2),
			error_msg("syntax error after token '|'"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_last_tkn(t_list **lst)
{
	t_list	*last;
	t_cmd	*last_cmd;

	last = ft_lstlast(*lst);
	last_cmd = (t_cmd *)last->content;
	if (last_cmd->token == REDIR_IN)
		return (exit_status(2),
			error_msg("syntax error after token '<'"), EXIT_FAILURE);
	if (last_cmd->token == REDIR_OUT)
		return (exit_status(2),
			error_msg("syntax error after token '>'"), EXIT_FAILURE);
	if (last_cmd->token == HERE_DOC)
		return (exit_status(2),
			error_msg("syntax error after token '<<'"), EXIT_FAILURE);
	if (last_cmd->token == APPEND)
		return (exit_status(2),
			error_msg("syntax error after token '>>'"), EXIT_FAILURE);
	if (last_cmd->token == PIPE)
		return (exit_status(2),
			error_msg("syntax error after token '|'"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_token_lst(t_list **lst)
{
	t_list		*tmp;
	t_cmd		*current_node;
	t_cmd		*next_node;

	if (!*lst)
		return (EXIT_FAILURE);
	if (check_last_tkn(lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tmp = *lst;
	if (((t_cmd *)(*lst)->content)->token == PIPE)
		return (exit_status(2),
			error_msg("syntax error near unexpected token '|'"), 1);
	while (tmp)
	{
		current_node = (t_cmd *)tmp->content;
		if (!tmp->next)
			next_node = NULL;
		else
			next_node = (t_cmd *)tmp->next->content;
		if (next_node && check_syntax_error(current_node, next_node))
			return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

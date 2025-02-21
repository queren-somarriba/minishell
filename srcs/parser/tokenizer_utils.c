/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:44:00 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 12:14:40 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_char_quoted(char *str, size_t index)
{
	size_t	i;
	size_t	mark;

	i = -1;
	while (str[++i] && i < index)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			mark = i;
			i += go_to_nextquote(str, i);
			if (index > mark && index < i)
				return (true);
		}
	}
	return (false);
}

size_t	count_arg_nbr(t_list *lst)
{
	t_list		*tmp;
	t_cmd		*cmd;
	size_t		count;

	count = 1;
	tmp = lst;
	if (tmp->next)
		cmd = (t_cmd *)tmp->next->content;
	else
		return (count);
	while (cmd->token != PIPE && tmp->next)
	{
		tmp = tmp->next;
		if (cmd->token == CMD_ARG)
			count++;
		cmd = (t_cmd *)tmp->content;
	}
	return (count);
}

static t_token	is_redirin_char(char *str, size_t index)
{
	if (str[index] == '<' && !is_char_quoted(str, index))
	{
		if (str[index + 1] && str[index + 1] == '<')
			return (HERE_DOC);
		if (str[index + 1] && str[index + 1] != '<')
		{
			if (index -1 <= 0)
			{
				if (str[index -1] != '<')
					return (REDIR_IN);
			}
			else
				return (REDIR_IN);
		}
		else
			return (REDIR_IN);
	}
	return (0);
}

t_token	is_meta_char(char *str, size_t index)
{
	if (str[index] == '|' && !is_char_quoted(str, index))
		return (PIPE);
	if (str[index] == '>' && !is_char_quoted(str, index))
	{
		if (str[index + 1] && str[index + 1] == '>')
			return (APPEND);
		if (str[index + 1] && str[index + 1] != '>')
		{
			if (index -1 <= 0)
			{
				if (str[index -1] != '>')
					return (REDIR_OUT);
			}
			else
				return (REDIR_OUT);
		}
		else
			return (REDIR_OUT);
	}
	return (is_redirin_char(str, index));
}

char	*get_one_token(char *str, size_t	index)
{
	char	*dest;
	size_t	i;

	i = index;
	while (str[i] && ft_is_white_space(str[i]))
			i++;
	if (!str[i])
		return (NULL);
	if (is_meta_char(str, i))
		++i;
	else
	{
		while (str[i] && ((!ft_is_white_space(str[i]) && !is_meta_char(str, i))
				|| (is_char_quoted(str, i))))
			++i;
	}
	if (str[i - 1] && is_meta_char(str, i - 1) != APPEND
		&& is_meta_char(str, i - 1) != HERE_DOC)
		--i;
	dest = ft_substr(str, index, i - index + 1);
	if (!dest)
		return (perror("malloc"), NULL);
	return (dest);
}

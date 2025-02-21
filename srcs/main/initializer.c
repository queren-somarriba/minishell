/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:17:16 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 12:09:18 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_cmd_line(void)
{
	char	*cmd_line;

	cmd_line = NULL;
	cmd_line = readline("minishell-$ ");
	return (cmd_line);
}

int	init_env(t_minishell *data, char **env)
{
	data->env = get_env(env);
	if (!data->env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_minishell(t_minishell *data, char **env)
{
	if (init_env(data, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->cmd_line = init_cmd_line();
	data->tkn_lst = NULL;
	data->stdin = -1;
	data->stdout = -1;
	return (EXIT_SUCCESS);
}

int	init_cmd_lst(t_minishell *data)
{
	char	*str;

	if (check_quotes(data->cmd_line))
		return (EXIT_SUCCESS);
	str = expand(data, data->cmd_line, 0);
	if (!str)
		return (perror("malloc"), EXIT_FAILURE);
	data->tkn_lst = tokenizer(str);
	free(str);
	handle_empty_tkn (data->tkn_lst, data);
	if (parser(data) == EXIT_FAILURE)
		return (free_tkn_lst(data->tkn_lst), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

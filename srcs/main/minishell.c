/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:11:52 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 17:29:48 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = EXIT_SUCCESS;

static int	x_tkn_lst(t_minishell *data)
{
	t_cmd	*tmp;

	if (data->tkn_lst && *data->tkn_lst)
	{
		if (lstfirst_cmd(*data->tkn_lst))
			tmp = (t_cmd *)lstfirst_cmd(*data->tkn_lst)->content;
	}
	if (data->tkn_lst && *data->tkn_lst)
	{
		if (lstsize_cmd(*data->tkn_lst) == 1 && tmp->cmd_arr
			&& is_builtin(*tmp->cmd_arr) && tmp->token == CMD)
		{
			if (redir_and_exec_builtin(tmp, data) == EXIT_FAILURE)
				return (free_tkn_lst(data->tkn_lst), 1);
		}
		else if (x_pipe(data))
			return (free_tkn_lst(data->tkn_lst), 1);
		free_tkn_lst(data->tkn_lst);
	}
	return (EXIT_SUCCESS);
}	

int	main(int ac, char **av, char **env)
{
	t_minishell	data;

	if (ac && av)
	{
		set_signal_action(0);
		if (init_minishell(&data, env))
			return (1);
		while (1)
		{
			if ((!data.cmd_line))
				builtin_exit(NULL, &data);
			if (!str_is_white_space(data.cmd_line))
				add_history(data.cmd_line);
			if (!init_cmd_lst(&data))
				x_tkn_lst(&data);
			data.tkn_lst = NULL;
			free(data.cmd_line);
			data.cmd_line = init_cmd_line();
		}
	}
	return (EXIT_SUCCESS);
}

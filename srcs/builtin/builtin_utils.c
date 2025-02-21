/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:12:09 by qsomarri          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:21 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *str)
{
	char	*builtin[8];
	size_t	i;

	i = -1;
	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = NULL;
	while (builtin[++i])
	{
		if (ft_str_equal(str, builtin[i]))
			return (true);
	}
	return (false);
}

int	exec_builtin(t_cmd *cmd, t_minishell *data)
{
	int	res;

	res = 1;
	if (ft_str_equal(cmd->cmd_arr[0], "pwd"))
		res = builtin_pwd(cmd->cmd_arr);
	else if (ft_str_equal(cmd->cmd_arr[0], "cd"))
		res = builtin_cd(cmd->cmd_arr, data);
	else if (ft_str_equal(cmd->cmd_arr[0], "env"))
		res = builtin_env(cmd->cmd_arr, data->env);
	else if (ft_str_equal(cmd->cmd_arr[0], "echo"))
		res = builtin_echo(cmd->cmd_arr);
	else if (ft_str_equal(cmd->cmd_arr[0], "export"))
		res = builtin_export(cmd->cmd_arr, data);
	else if (ft_str_equal(cmd->cmd_arr[0], "unset"))
		res = builtin_unset(cmd->cmd_arr, data);
	else if (ft_str_equal(cmd->cmd_arr[0], "exit"))
		res = builtin_exit(cmd->cmd_arr, data);
	return (res);
}

int	redir_and_exec_builtin(t_cmd *cmd, t_minishell *data)
{
	int	res;

	res = -1;
	if (cmd->redir_lst)
	{
		if (dup_stds(data))
			return (EXIT_FAILURE);
		if (x_redir_lst(cmd->redir_lst))
			return (exit_status(1), restore_stds(data), 1);
	}
	res = exec_builtin(cmd, data);
	g_exit_status = res;
	if (cmd->redir_lst)
	{
		if (restore_stds(data))
			return (EXIT_FAILURE);
	}
	return (res);
}

void	swap_str(char **str1, char **str2)
{
	char	*swap;

	swap = *str1;
	*str1 = *str2;
	*str2 = swap;
}

void	sort_array(char **arr)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (arr[++i])
	{
		j = i;
		while (arr[++j])
		{
			if (ft_strncmp(arr[i], arr[j],
					ft_min(ft_strlen(arr[i]), ft_strlen(arr[j]))) > 0)
				swap_str(&arr[i], &arr[j]);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:12:34 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/14 18:29:15 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_env_flag(char *str)
{
	if (ft_str_equal(str, "-i") || ft_str_equal(str, "-0")
		|| ft_str_equal(str, "-u")
		|| ft_str_equal(str, "-c") || ft_str_equal(str, "-s")
		|| ft_str_equal(str, "--block-signal")
		|| ft_str_equal(str, "--default-signal")
		|| ft_str_equal(str, "--ignore-signal")
		|| ft_str_equal(str, "--list-signal-handling")
		|| ft_str_equal(str, "-v")
		|| ft_str_equal(str, "--help") || ft_str_equal(str, "--version"))
		return (error_msg2("env: minishell doesn't handle this option: ", str),
			false);
	else
		return (true);
}

int	builtin_env(char **arr, char **env)
{
	if (arr[1])
	{
		if (!is_valid_env_flag(arr[1]))
			return (2);
		else if (!ft_strncmp(arr[1], "-", 1))
			return (error_msg2("env: invalid option: ", arr[1]), 2);
		else if (!access(arr[1], F_OK))
			return (error_msg2("env: Permission denied: ", arr[1]), 126);
		else
			return (error_msg2("env: No such file or directory: ", arr[1]),
				127);
	}
	while (*env)
	{
		if (printf("%s\n", *env++) < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

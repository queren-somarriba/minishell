/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:53 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 17:18:27 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_pwd_flag(char *str)
{
	if ((ft_str_equal(str, "-L")) || (ft_str_equal(str, "-P"))
		|| (ft_str_equal(str, "--help")) || (ft_str_equal(str, "--version")))
		return (error_msg2("pwd: minishell doesn't handle this option: ", str),
			false);
	if (ft_str_equal(str, "-") || ft_str_equal(str, "--"))
		return (true);
	else if (str[0] == '-')
		return (error_msg2("pwd: invalid option: ", str), false);
	else
		return (true);
}

int	builtin_pwd(char **arr)
{
	char	*cwd;

	if (arr[1])
	{
		if (!is_valid_pwd_flag(arr[1]))
			return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd()"), EXIT_FAILURE);
	else
	{
		if (printf("%s\n", cwd) < 0)
			return (free(cwd), EXIT_FAILURE);
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

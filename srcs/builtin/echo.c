/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:33:18 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 18:11:00 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_echo_flag(char *str)
{
	size_t	i;

	i = -1;
	if ((ft_str_equal(str, "-e")) || (ft_str_equal(str, "-E"))
		|| (ft_str_equal(str, "--help")) || (ft_str_equal(str, "--version")))
		return (error_msg2("echo: minishell doesn't handle this option: ",
				str), -1);
	if (str[0] == '\0')
		return (false);
	while (str[++i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		if (str[i] != 'n' || (i == 0 && str[i] == 'n'))
			return (false);
	}
	return (true);
}

static int	print_arg(char **arr, size_t index)
{
	while (arr[++index])
	{
		if (ft_printf("%s", arr[index]) < 0)
			return (EXIT_FAILURE);
		if (arr[index + 1])
		{
			if (ft_printf(" ") != 1)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_echo(char **cmd)
{
	size_t	i;
	int		res;

	i = 0;
	if (!cmd[1])
		return (ft_putstr_fd("\n", 1), EXIT_SUCCESS);
	res = is_valid_echo_flag(cmd[1]);
	if (res == -1)
		return (2);
	if (res)
	{
		while (cmd[++i] && is_valid_echo_flag(cmd[i]))
			continue ;
		if (print_arg(cmd, --i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (print_arg(cmd, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (printf("\n") != 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}		

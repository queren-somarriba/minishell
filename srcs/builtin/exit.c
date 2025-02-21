/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:10:00 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/14 18:28:07 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check if the string of char representing the long number
will overflow with ft_atol*/
static	bool	is_zero_nptr(char *nptr)
{
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr)
	{
		if (*nptr != '0')
			return (false);
		nptr++;
	}
	return (true);
}

static	bool	nptr_is_long(char *nptr)
{
	long	atol_nptr;
	char	*tmp;

	if (is_zero_nptr(nptr))
		return (true);
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr == '0')
		nptr++;
	atol_nptr = ft_atol(nptr);
	tmp = ft_ltoa(atol_nptr);
	if (!ft_str_equal(nptr, tmp))
		return (free(tmp), false);
	return (free(tmp), true);
}

static bool	is_valid_exit_arg(char *str)
{
	size_t		i;

	i = -1;
	if (ft_str_equal(str, "-") || ft_str_equal(str, "+")
		|| !nptr_is_long(str) || str[0] == '\0')
		return (error_msg2(
				"exit: numeric argment required: ", str), false);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (error_msg2(
					"exit: numeric argment required: ", str), false);
	}
	return (true);
}

void	close_free_and_exit(long exit_code, t_minishell *data)
{
	close_stds(data);
	free_minishell(data);
	exit(exit_code);
}

int	builtin_exit(char **arr, t_minishell *data)
{
	long	exit_code;

	if (printf("exit\n") < 0)
		return (perror("printf"), EXIT_FAILURE);
	if (!arr || !arr[1] || ft_str_equal(arr[1], "-9223372036854775808"))
		close_free_and_exit(0, data);
	exit_code = ft_atol(arr[1]);
	if (arr[2])
	{
		if (!is_valid_exit_arg(arr[1]))
			close_free_and_exit(2, data);
		return (error_msg("exit: too many arguments"), EXIT_FAILURE);
	}
	else
	{
		if (!is_valid_exit_arg(arr[1]))
			exit_code = 2;
		close_free_and_exit(exit_code, data);
	}
	return (EXIT_FAILURE);
}

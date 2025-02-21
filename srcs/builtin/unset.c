/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:39:44 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 11:19:55 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_unset_flag(char *str)
{
	if ((ft_str_equal(str, "-f")) || (ft_str_equal(str, "-v"))
		|| (ft_str_equal(str, "-n")) || (ft_str_equal(str, "--help")))
		return (error_msg2("unset: minishell doesn't handle this option: ",
				str),
			false);
	else if (str[0] == '-' && str[1])
		return (error_msg2("unset: invalid option: ", str), false);
	else
		return (true);
}

static bool	is_env_var(char *str, t_minishell *data)
{
	size_t	i;

	i = -1;
	while (data->env[++i])
	{
		if (str[0] == '\0')
			return (false);
		if (!ft_strncmp(str, data->env[i], ft_strlen(str)))
			return (true);
	}
	return (false);
}

int	make_env_without_str(char *str, char **new_env, t_minishell *data)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(str, data->env[i], var_name_len(data->env[i]))
			&& var_name_len(str) != var_name_len(data->env[i]))
		{
			new_env[++j] = ft_strdup(data->env[i]);
			if (!new_env[j])
				return (perror("malloc"), EXIT_FAILURE);
		}
		free(data->env[i]);
	}
	new_env[++j] = NULL;
	return (EXIT_SUCCESS);
}

int	unset_var(char *str, t_minishell *data)
{
	char	**new_env;
	size_t	i;

	i = -1;
	while (data->env[++i])
		continue ;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (error_msg("unset: malloc"), EXIT_FAILURE);
	if (make_env_without_str(str, new_env, data) == EXIT_FAILURE)
		return (ft_free_array(new_env), EXIT_FAILURE);
	free(data->env);
	data->env = new_env;
	return (EXIT_SUCCESS);
}

int	builtin_unset(char **arr, t_minishell *data)
{
	size_t	i;

	i = 0;
	if (!arr[1])
		return (EXIT_SUCCESS);
	if (ft_str_equal(arr[1], "_"))
		return (EXIT_SUCCESS);
	if (is_valid_unset_flag(arr[1]))
	{
		while (arr[++i])
		{
			if (is_env_var(arr[i], data))
			{
				if (unset_var(arr[i], data) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
	}
	else
		return (2);
	return (EXIT_SUCCESS);
}

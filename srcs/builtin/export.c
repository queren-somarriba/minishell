/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:28:49 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 18:54:31 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export_arg(char *str)
{
	size_t	i;

	i = 0;
	if (ft_str_equal(str, "-p"))
		return (error_msg2(
				"export: minishell doesn't handle this option: ", str), 2);
	if (!ft_strncmp(str, "-", 1))
		return (error_msg2("export: invalid option: ", str), 2);
	if (str[0] != '_' && !(str[0] >= 'A' && str[0] <= 'Z')
		&& !(str[0] >= 'a' && str[0] <= 'z'))
		return (error_msg2("export: not a valid identifier: ", str), 1);
	while (str[++i] && str[i] != '=')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (error_msg2("export: not a valid identifier: ", str), 1);
	}
	return (0);
}

static int	display_export_var(char *str)
{
	size_t	i;

	i = -1;
	if (ft_strncmp(str, "_=", 2))
	{
		if (write(1, "export ", 7) != 7)
			return (perror("write"), EXIT_FAILURE);
		while (str[++i] && str[i] != '=')
			if (write(1, &str[i], 1) != 1)
				return (perror("write"), EXIT_FAILURE);
		if (str[i])
		{
			if (write(1, "=\"", 2) != 2)
				return (perror("write"), EXIT_FAILURE);
			while (str[++i])
				if (write(1, &str[i], 1) != 1)
					return (perror("write"), EXIT_FAILURE);
			if (write(1, "\"", 1) != 1)
				return (perror("write"), EXIT_FAILURE);
		}
		if (write(1, "\n", 1) != 1)
			return (perror("write"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_with_no_arg(char **env)
{
	size_t	i;

	i = -1;
	sort_array(env);
	while (env[++i])
	{
		if (display_export_var(env[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_with_arg(char *var, t_minishell *data)
{
	char	**new_env;
	size_t	i;

	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(var, data->env[i], var_name_len(data->env[i]))
			&& var_name_len(data->env[i]) == var_name_len(var))
			return (update_env_var2(var, data->env), EXIT_SUCCESS);
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (error_msg("export: malloc"), EXIT_FAILURE);
	if (add_var_to_env(var, new_env, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free_array(data->env);
	init_env(data, new_env);
	ft_free_array(new_env);
	return (EXIT_SUCCESS);
}

int	builtin_export(char **arr, t_minishell *data)
{
	size_t	i;
	int		res[2];

	i = 0;
	res[0] = 0;
	res[1] = 0;
	if (arr[1])
	{
		while (arr[++i])
		{
			res[0] = is_valid_export_arg(arr[i]);
			if (!res[0])
			{
				if (export_with_arg(arr[i], data) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			else
				res[1] = res[0];
		}
	}
	else
		if (export_with_no_arg(data->env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (res[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:49 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/14 18:44:52 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_env(char **env)
{
	char	**new_env;
	char	*tmp;

	tmp = NULL;
	new_env = malloc(sizeof(char *) * 4);
	if (!new_env)
		return (perror("malloc"), NULL);
	if (!*env)
	{
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (perror("getcwd"), NULL);
		new_env[0] = ft_strjoin("PWD=", tmp);
		if (!new_env[0])
			return (perror("malloc"), free(tmp),
				ft_free_array(new_env), NULL);
		new_env[1] = ft_strdup("SHLVL=1");
		if (!new_env[1])
			return (perror("malloc"), ft_free_array(new_env), NULL);
		new_env[2] = ft_strdup("_=/usr/bin/env");
		if (!new_env[2])
			return (perror("malloc"), ft_free_array(new_env), NULL);
		new_env[3] = NULL;
	}
	return (free(tmp), new_env);
}

char	**get_env(char **env)
{
	char	**new_env;
	size_t	i;

	i = -1;
	if (!*env)
		return (make_env(env));
	while (env[++i])
		continue ;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (perror("malloc"), NULL);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "_=/", 3))
			new_env[i] = ft_strdup("_=/usr/bin/env");
		else
			new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (perror("malloc"), ft_free_array(new_env), NULL);
	}
	new_env[i] = NULL;
	return (new_env);
}

/*update an evironment variable by passing the name of the variable as var_name
and the new value of the variable as str; ex:
update_env_var("PWD=", new_pwd, env);*/
int	update_env_var(const char *var_name, char *str, char **env)
{
	size_t	i;

	i = -1;
	if (!str)
		return (EXIT_FAILURE);
	while (env[++i])
	{
		if (!ft_strncmp(var_name, env[i], var_name_len(env[i]))
			&& var_name_len(env[i]) == var_name_len((char *)var_name))
		{
			free(env[i]);
			env[i] = ft_strjoin(var_name, str);
			if (!env[i])
				return (perror("malloc"), EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

/*update an environment variable by passing the name of the variable
and the new value in a string of char; ex:
update_env_var2("PWD=new_pwd", env);*/
int	update_env_var2(char *str, char **env)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (env[++i])
	{
		if (!ft_strncmp(str, env[i], var_name_len(env[i]))
			&& var_name_len(env[i]) == var_name_len(str))
		{
			while (str[++j] && str[j] != '=')
				continue ;
			if (j == ft_strlen(str))
				break ;
			free(env[i]);
			env[i] = ft_strdup(str);
			if (!env[i])
				return (perror("malloc"), EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	add_var_to_env(char *var, char **new_env, t_minishell *data)
{
	size_t	i;

	i = -1;
	while (data->env[++i])
	{
		new_env[i] = ft_strdup(data->env[i]);
		if (!new_env[i])
			return (perror("malloc"),
				ft_free_array(new_env), EXIT_FAILURE);
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (perror("malloc"), ft_free_array(new_env), EXIT_FAILURE);
	new_env[++i] = NULL;
	return (EXIT_SUCCESS);
}

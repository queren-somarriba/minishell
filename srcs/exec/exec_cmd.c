/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:09 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 12:01:16 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_path(char **env, t_minishell *data)
{
	char	*getpaths;
	char	**paths;

	getpaths = NULL;
	paths = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			getpaths = ft_substr(*env, 5, ft_strlen(*env) - 4);
			break ;
		}
		env++;
	}
	if (!getpaths)
		return (free_minishell (data),
			error_msg("TERM environment variable not set"), NULL);
	paths = ft_split(getpaths, ':');
	free(getpaths);
	if (!paths)
		return (free_minishell(data), perror("ok"), NULL);
	return (paths);
}

static int	x_absolut_path(char **cmd, char **env)
{
	if (cmd[0][0] != '/')
		return (EXIT_FAILURE);
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
			return (perror("execve"), EXIT_FAILURE);
	}
	if (cmd[0][0] == '/')
		return (127);
	return (EXIT_SUCCESS);
}

static int	x_cmd_name(char **paths, char **cmd, char **env, t_minishell *data)
{
	size_t	i;
	char	*tmp;

	i = -1;
	while (paths[++i] && cmd[0][0] != '\0')
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(paths[i], X_OK) == 0)
			if (execve(paths[i], cmd, env) == -1)
				return (ft_free_array(paths), free_minishell(data),
					perror("execve"), EXIT_FAILURE);
	}
	if (!paths[i] || cmd[0][0] == '\0')
	{
		ft_free_array(paths);
		if (!ft_strncmp(cmd[0], "./", 2) && !access(&cmd[0][2], F_OK))
			return (error_msg2(cmd[0], ": Permission denied"),
				free_minishell(data), 126);
		return (error_msg2(cmd[0], ": command not found"),
			free_minishell(data), 127);
	}
	return (EXIT_SUCCESS);
}

static int	x_in_cwd(char **cmd, char **env)
{
	char	*path;
	char	*tmp;

	if (cmd[0][0] == '\0')
		return (EXIT_FAILURE);
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (perror("malloc"), free(path), EXIT_FAILURE);
	free(path);
	path = ft_strjoin(tmp, cmd[0]);
	if (!path)
		return (perror("malloc"), free(tmp), EXIT_FAILURE);
	free(tmp);
	if (access(path, X_OK) == 0)
	{
		if (execve(path, cmd, env) == EXIT_FAILURE)
			return (free(path), EXIT_FAILURE);
		return (free(path), EXIT_SUCCESS);
	}
	return (free(path), EXIT_FAILURE);
}

int	x_cmd(char **argv, char **env, t_minishell *data)
{
	char	**paths;
	int		res;

	paths = NULL;
	if (!argv)
		return (free_minishell(data), EXIT_FAILURE);
	if ((!ft_strncmp(argv[0], "./", 2) && is_directory(&argv[0][2]))
		|| is_directory(argv[0]))
	{
		error_msg2(argv[0], ": Is a directory");
		free_minishell(data);
		exit(126);
	}
	res = x_absolut_path(argv, env);
	if (res == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	res = x_in_cwd(argv, env);
	if (res == EXIT_SUCCESS)
		return (res);
	paths = split_env_path(env, data);
	if (!paths)
		return (EXIT_FAILURE);
	res = x_cmd_name(paths, argv, env, data);
	return (res);
}

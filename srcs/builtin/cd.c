/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:28 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 18:10:44 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_cd_flag(char **arr)
{
	if ((ft_str_equal(arr[0], "-L")) || (ft_str_equal(arr[1], "-P")))
		return (error_msg2("cd: minishell doesn't handle this option: ",
				arr[1]), false);
	else if (!ft_str_equal(arr[1], "-") && !ft_strncmp(arr[1], "-", 1))
		return (error_msg2("cd: invalid option: ", arr[1]), false);
	else
		return (true);
}

static int	cd_with_no_arg(char *oldpwd, t_minishell *data)
{
	char	*cwd;

	cwd = get_var_value("HOME=", data->env);
	if (!oldpwd)
		oldpwd = get_var_value("PWD=", data->env);
	if (!cwd)
		return (free(oldpwd), error_msg("cd : HOME not set"), 1);
	if (cwd[0] == '\0')
		return (free(cwd), free(oldpwd), EXIT_SUCCESS);
	if (chdir(cwd) == -1)
		return (free(cwd), free(oldpwd), error_msg("cd: HOME not set"), 1);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (update_env_var("OLDPWD=", oldpwd, data->env) == EXIT_FAILURE
		|| update_env_var("PWD=", cwd, data->env) == EXIT_FAILURE)
		return (free(cwd), free(oldpwd), EXIT_FAILURE);
	return (free(cwd), free(oldpwd), EXIT_SUCCESS);
}

static int	update_pwd_oldpwd_var(char *oldpwd, t_minishell *data)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = get_var_value("PWD=", data->env);
	if (update_env_var("OLDPWD=", oldpwd, data->env) == EXIT_FAILURE)
	{
		if (oldpwd)
		{
			tmp = ft_strjoin("OLDPWD=", oldpwd);
			export_with_arg(tmp, data);
			free(tmp);
		}
	}
	if (update_env_var("PWD=", cwd, data->env) == EXIT_FAILURE)
		return (free(cwd), free(oldpwd), EXIT_FAILURE);
	return (free(cwd), free(oldpwd), EXIT_SUCCESS);
}

static int	cd_oldpwd(char *oldpwd, t_minishell *data)
{
	char	*tmp;

	tmp = get_var_value("OLDPWD=", data->env);
	if (!oldpwd)
		oldpwd = get_var_value("PWD=", data->env);
	if (tmp && access(tmp, F_OK))
		return (error_msg2(CD_ERROR1, tmp),
			free(tmp), free(oldpwd), EXIT_FAILURE);
	if (tmp && !chdir(tmp))
	{
		update_pwd_oldpwd_var(oldpwd, data);
		if (printf("%s\n", tmp) < 0)
			return (free(tmp), EXIT_FAILURE);
		return (free(tmp), EXIT_SUCCESS);
	}
	else
		return (error_msg("cd: OLPWD not set"),
			free(tmp), free(oldpwd), EXIT_FAILURE);
	return (free(tmp), free(oldpwd), EXIT_FAILURE);
}

int	builtin_cd(char **arr, t_minishell *data)
{
	char	*oldpwd;
	int		res;

	oldpwd = getcwd(NULL, 0);
	if (arr[1] && !is_valid_cd_flag(arr))
		return (free(oldpwd), 2);
	if (!arr[1])
		return (cd_with_no_arg(oldpwd, data));
	if (arr[1] && arr[2])
		return (free(oldpwd), error_msg("cd: too many arguments"), 1);
	if (arr[1][0] == '\0')
		return (free(oldpwd), EXIT_SUCCESS);
	if (!is_directory(arr[1]) && !access(arr[1], F_OK))
		return (free(oldpwd), error_msg2(CD_ERROR2, arr[1]), 1);
	else if (!is_directory(arr[1]) && ft_str_equal(arr[1], "-"))
		return (cd_oldpwd(oldpwd, data));
	else if (!is_directory(arr[1]))
		return (free(oldpwd), error_msg2(CD_ERROR1, arr[1]), 1);
	res = chdir(arr[1]);
	if (!res && !oldpwd)
		return (free(oldpwd), error_msg2(CD_ERROR1, arr[1]), 1);
	if (!res)
		return (update_pwd_oldpwd_var(oldpwd, data));
	return (free(oldpwd),
		error_msg2("cd: Permission denied : ", arr[1]), EXIT_FAILURE);
}

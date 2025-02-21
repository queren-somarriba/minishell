/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:46:31 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 11:37:23 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_white_space(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isprint(str[i]) && str[i] != ' ')
			return (0);
	}
	return (1);
}

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!stat(path, &path_stat))
		return (S_ISDIR(path_stat.st_mode));
	else
		return (false);
}

char	*get_var_value(char *var_name, char **env)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	dest = NULL;
	if (!var_name)
		return (NULL);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, var_name_len(var_name)))
		{
			while (env[i][++j] && env[i][j] != '=')
				continue ;
			if (env[i][j] == '=')
			{
				dest = ft_strdup(&env[i][++j]);
				if (!dest)
					return (perror("malloc"), NULL);
			}
			return (dest);
		}
	}
	return (dest);
}

size_t	var_name_len(char *str)
{
	size_t	len;

	len = -1;
	if (!str)
		return (0);
	while (str[++len] && str[len] != '=')
		continue ;
	return (len);
}

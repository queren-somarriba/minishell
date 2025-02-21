/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:09:36 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/19 18:05:45 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_var(char *str, char *var, size_t index)
{
	char	*dest;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(var, 0, var_name_len(var));
	tmp2 = ft_strjoin(tmp, "=");
	free(tmp);
	tmp = get_var_value(tmp2, &var);
	free(tmp2);
	dest = ft_substr(str, 0, index - 1);
	tmp2 = ft_strjoin(dest, tmp);
	free(dest);
	free(tmp);
	tmp = ft_strdup(&str[index + var_name_len(var)]);
	dest = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (dest);
}

static char	*expand_questmark(char *str, size_t index)
{
	char	*dest;
	char	*tmp;
	char	*tmp2;

	dest = ft_substr(str, 0, index - 1);
	tmp = ft_itoa(g_exit_status);
	tmp2 = ft_strjoin(dest, tmp);
	free(dest);
	free(tmp);
	tmp = ft_strdup(&str[index + 1]);
	dest = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (dest);
}

static char	*expand_dollar(t_minishell *data, char *str, size_t index)
{
	char	*dollar_str;
	size_t	j;
	size_t	dollar_str_len;

	j = -1;
	dollar_str = dollar_varname(str);
	dollar_str_len = ft_strlen(dollar_str);
	if (str[index] == '?')
		return (free(dollar_str), expand_questmark(str, index));
	else if (dollar_str[0] == '\0')
		return (free(dollar_str), remove_dollar(str, index - 1));
	else
	{
		while (data->env[++j])
		{
			if (!ft_strncmp(dollar_str, data->env[j], dollar_str_len)
				&& dollar_str_len == var_name_len(data->env[j]))
				return (free(dollar_str),
					expand_env_var(str, data->env[j], index));
		}
	}
	return (free(dollar_str), expand_no_var(str, dollar_str_len, index));
}

static char	*handle_expansion(t_minishell *data, char *str, size_t *i)
{
	char	*tmp;
	size_t	j;

	j = 0;
	if (str[*i] == '\'' && *i >= j)
		*i += go_to_nextquote(str, *i);
	if (str[*i] == '$' && str[*i + 1])
	{
		if (!check_dollar(str, *i))
		{
			tmp = ft_strdup(str);
			free(str);
			str = expand_dollar(data, tmp, *i + 1);
			if (!str)
				return (free(tmp), NULL);
			free(tmp);
			*i = -1;
			j = 0;
		}
	}
	return (str);
}

char	*expand(t_minishell *data, char *str, int mode)
{
	char	*dest;
	char	*tmp;
	size_t	i;

	i = -1;
	if (!str)
		return (NULL);
	tmp = ft_strdup(str);
	while (tmp && tmp[++i])
	{
		dest = ft_strdup(tmp);
		free(tmp);
		tmp = handle_expansion(data, dest, &i);
		if (!tmp)
			return (free(dest), NULL);
	}
	if (mode == 1 && count_quotes(tmp) % 2 == 0)
		dest = remove_quotes(tmp);
	else
		dest = ft_strdup(tmp);
	return (free(tmp), dest);
}

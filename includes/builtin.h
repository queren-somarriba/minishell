/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:59:33 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 16:56:58 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "type.h"

# define CD_ERROR1 "cd: No such file or directory: "
# define CD_ERROR2 "cd: Not a directory: "

/*BUILTIN_UTILS*/
bool	is_builtin(char *cmd);

int		exec_builtin(t_cmd *cmd, t_minishell *data);

int		redir_and_exec_builtin(t_cmd *cmd, t_minishell *data);

void	swap_str(char **str1, char **str2);

void	sort_array(char **tab);

/*CD*/
int		builtin_cd(char **cmd, t_minishell *data);

/*ECHO*/
int		builtin_echo(char **cmd);

/*ENV*/
int		builtin_env(char **cmd, char **env);

/*ENV_UTILS*/
char	**get_env(char **envp);

char	**make_env(char **env);

int		update_env_var(const char *var, char *str, char **env);

int		update_env_var2(char *str, char **env);

int		add_var_to_env(char *var, char **new_env, t_minishell *data);

/*EXIT*/
int		builtin_exit(char **cmd, t_minishell *data);

/*EXPORT*/
int		builtin_export(char **cmd, t_minishell *data);

int		export_with_arg(char *var, t_minishell *data);

/*PWD*/
int		builtin_pwd(char **cmd);

/*UNSET*/
int		builtin_unset(char **cmd, t_minishell *data);

#endif

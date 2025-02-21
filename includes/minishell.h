/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:40:42 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/12 10:35:41 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*EXTERN LIBRARY*/
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <linux/limits.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <dirent.h>

/*INTERN LIBRARY*/
# include "builtin.h"

# include "error_mgmt.h"

# include "exec.h"

# include "parser.h"

# include "redirections.h"

# include "type.h"

/*GLOBAL VARIABLE*/
extern int	g_exit_status;

/*INITIALIZER*/
int		init_minishell(t_minishell *data, char **env);

int		init_env(t_minishell *data, char **env);

int		init_cmd_lst(t_minishell *data);

char	*init_cmd_line(void);

/*LIST_UTILS*/

t_list	*lstlast_cmd(t_list *lst);

t_list	*lstfirst_cmd(t_list *lst);

size_t	lstsize_cmd(t_list *lst);

void	handle_empty_tkn(t_list **lst, t_minishell *data);

/*MINISHELL_UTILS*/
bool	is_directory(const char *path);

char	*get_var_value(char *var, char **env);

size_t	var_name_len(char *str);

int		str_is_white_space(char *str);

#endif

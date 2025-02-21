/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:22:15 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/06 16:38:42 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef enum e_token
{
	CMD,
	REDIR_IN,
	HERE_DOC,
	REDIR_OUT,
	APPEND,
	PIPE,
	CMD_ARG,
	TARGET
}			t_token;

typedef struct s_redir
{
	char	*target;
	int		type;
	int		fd;
}				t_redir;

typedef struct s_cmd
{
	char			*tkn_str;
	char			**cmd_arr;
	t_redir			*redir;
	t_token			token;
	t_list			**redir_lst;
}			t_cmd;

typedef struct s_here_doc_str
{
	char	*str;
	char	*line;
	char	*delimiter;
	char	*tmp;
}		t_here_doc_str;

typedef struct s_minishell
{
	char	**env;
	t_list	**tkn_lst;
	char	*cmd_line;
	int		stdin;
	int		stdout;
}			t_minishell;

#endif

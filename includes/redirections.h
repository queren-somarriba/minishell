/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:54:35 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 19:24:42 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

/*HERE_DOC*/
int		heredoc_manage(char *str, t_minishell *data, t_list **redir_lst);

/*REDIRECTIONS*/
int		parse_redirection(t_redir *redir);

/*REDIRECTIONS_UTILS*/
int		x_redir_lst(t_list **lst);

int		dup_stds(t_minishell *data);

int		restore_stds(t_minishell *data);

int		close_stds(t_minishell *data);

#endif

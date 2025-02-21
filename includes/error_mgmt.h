/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmt.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:00:04 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/12 15:23:28 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MGMT_H
# define ERROR_MGMT_H

/*CHECK_PARS_ERROR*/
int		check_quotes(char *str);

int		check_token_lst(t_list **lst);

/*FREE*/
void	free_minishell(t_minishell *data);

void	free_tkn_lst(t_list	**tkn_lst);

void	free_redir_lst(t_list	**lst);

void	free_tkn_node(t_list *node);

/*OUTPUTS*/
void	exit_status(int nbr);

void	error_msg(char *msg);

void	error_msg2(char *msg, char *str);

/*SIGNAL_HANDLER*/
void	set_signal_action(int mode);

#endif

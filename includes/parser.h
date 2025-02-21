/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:07:33 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/18 19:23:59 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*EXPANSION*/
char	*expand(t_minishell *data, char *str, int mode);

/*EXPANSION UTILS*/
char	*remove_dollar(char *str, size_t index);

char	*dollar_varname(char *str);

bool	check_dollar(char *str, size_t index);

char	*expand_no_var(char *str, size_t dollar_str_len, size_t index);

/*PARSER*/
int		make_cmd_lst(char **arr, t_minishell *data);

int		check_token_lst(t_list **lst);

int		parser(t_minishell *data);

/*PARSER2*/
int		fillup_cmd_node(t_minishell *data, t_list *node, t_list **lst);

/*PARSER_UTILS*/
t_token	is_meta_char(char *str, size_t index);

bool	is_space(char c);

bool	is_char_quoted(char *str, size_t index);

size_t	count_arg_nbr(t_list *lst);

char	*get_one_token(char *str, size_t	index);

/*QUOTES*/
char	*remove_quotes(char *str);

size_t	count_quotes(char *str);

size_t	go_to_nextquote(char *str, size_t index);

char	**split_and_remove_quotes(char *str);

/*TOKENIZER*/
char	*get_one_token(char *str, size_t index);

t_list	**tokenizer(char *str);

#endif

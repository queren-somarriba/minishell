/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <qsomarri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:17:26 by qsomarri          #+#    #+#             */
/*   Updated: 2025/02/12 19:30:11 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		ft_lstadd_front(lst, new);
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstadd_before(t_list **lst, t_list *node, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (!node->next)
	{
		ft_lstadd_back(lst, new);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	tmp->next = new;
	new->next = node;
}

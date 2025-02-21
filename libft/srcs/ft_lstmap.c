/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:44:15 by qsomarri          #+#    #+#             */
/*   Updated: 2024/05/31 18:49:28 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;
	void	*new_content;

	tmp = NULL;
	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = (*f)(lst->content);
		tmp = ft_lstnew(new_content);
		if (tmp == NULL)
		{
			if (new_content)
				del(new_content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, tmp);
		lst = lst->next;
	}
	return (head);
}

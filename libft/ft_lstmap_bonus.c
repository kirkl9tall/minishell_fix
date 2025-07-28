/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:09:22 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/12 21:47:11 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	head = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		if (!head)
			head = node;
		else
			ft_lstadd_back(&head, node);
		lst = lst->next;
	}
	return (head);
}
/*
ft_lstadd_back(&list, ft_lstnew(val));
mapped_list = ft_lstmap(list, f, del);
   printf("%d\n", *(int *)mapped_list->content);
*/
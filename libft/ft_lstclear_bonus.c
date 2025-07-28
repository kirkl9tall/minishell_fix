/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:18:33 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/07 22:36:56 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*clear;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		clear = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = clear;
	}
	*lst = NULL;
}

/*int main ()
{
t_list	*head;
t_list	*a;
t_list	*b;
t_list	*c;
t_list	*k;
k = malloc (sizeof(struct s_list));
a = malloc (sizeof(struct s_list));
   b = malloc (sizeof(struct s_list));
	c = malloc (sizeof(struct s_list ));

a->next = b;
b->next = c;
c->next = NULL;
head = a;
ft_lstdelone(a,del);
//head = a->next;
int m =ft_lstsize(head);
//printf ("%p\n",(void *)a);
printf ("%d",m);
}*/
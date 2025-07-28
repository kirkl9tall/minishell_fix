/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:19:40 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/07 20:41:21 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
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
   b = malloc (sizeof(struct  s_list));
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
/*void del(void *content)
{
   free(content);
}*/
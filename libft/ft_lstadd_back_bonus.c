/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:33:07 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/07 20:38:38 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}

/*int main ()
{
t_list	*head;
t_list	*a;
t_list	*b;
t_list	*c;
t_list	*k;
k = malloc(sizeof(struct ali));
a = malloc (sizeof(struct ali));
b = malloc (sizeof(struct ali));
c = malloc (sizeof(struct ali));

a->next = b;
b->next = c;
c->next = NULL;
head = a;
 ft_lstadd_back(&head,k);
int		m = ft_lstsize (head);
k->next = NULL;

printf("%d",m);
}*/
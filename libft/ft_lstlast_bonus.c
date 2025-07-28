/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:25:04 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/08 20:41:31 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/*int main ()
{
	t_list *head;
  t_list *a;
  t_list *b;
  t_list *c;
  a = malloc (sizeof(struct s_list));
   b = malloc (sizeof(struct  s_list));
	c = malloc (sizeof(struct s_list ));
  if(!a || !b ||!c)
	return(0);
  a->next = b;
   b->next = c;
	c->next = NULL;
	c->content = "aaaa";
  head = ft_lstlast(a);
  printf ("%s",(char *)(head->content));
}*/
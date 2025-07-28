/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:35:15 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/07 20:42:50 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/*int main ()
{
   t_list *head = NULL;
  t_list *a ;
  t_list *b ;
  t_list *c ;
  a = malloc (sizeof(struct s_list));
   b = malloc (sizeof(struct  s_list));
	c = malloc (sizeof(struct s_list ));
  if(!a || !b ||!c)
	return(0);
  a->next = b;
   b->next = c;
	c->next = NULL;
  printf("%d",ft_lstsize(a));
}*/
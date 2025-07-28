/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:35:53 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 16:13:31 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
void	ft_add(void *content)
{
	int	*value;

		value = (int *)content;
		(*value)++;
}
int main ()
{
	t_list *head;
	t_list *c;
	t_list *a;
	t_list *b;

	c = malloc (sizeof(struct s_list));
	a = malloc (sizeof(struct s_list));
	b = malloc (sizeof(struct s_list));

	if (!a || !c || !b)
		return(0);
	a->next = b;
		b->next = c;
		c->next =NULL;
	head = a;
   a->content = malloc(sizeof(int));
	b->content = malloc(sizeof(int));
	c->content = malloc(sizeof(int));
	if (!a->content || !b->content || !c->content)
		return (1);
   *(int *)(a->content) = 1;
	*(int *)(b->content) = 3;
	*(int *)(c->content) = 5;
	ft_lstiter(a,ft_add);
		ft_lstiter(b,ft_add);
		ft_lstiter(c,ft_add);
	printf ("%d",*(int *)(a->content));
	printf ("%d",*(int *)(b->content));
	printf ("%d",*(int *)(c->content));
}*/

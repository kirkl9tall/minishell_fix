/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:39:49 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 21:46:29 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*int main(void)
{
	t_list *lst = NULL;
	t_list *new = malloc(sizeof(t_list));

	new->content = "First";
	new->next = NULL;
	ft_lstadd_front(&lst, new);

	printf("%s\n", (char *)lst->content);  // Expected: "First"
	return (0);
}*/

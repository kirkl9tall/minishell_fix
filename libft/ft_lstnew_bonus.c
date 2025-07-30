/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:35:58 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 21:04:09 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
    gr_t(node , 0);	
	// if (!node)
	// 	return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/*int main(void)
{
	t_list *node = ft_lstnew("Hello, World!");
	if (node)
		printf("%s\n", (char *)node->content);
	free(node);
	return (0);
}*/
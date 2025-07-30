/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:21:46 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 21:03:40 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
    gr_t(p , 0);
	// if (p == NULL)
	// 	return (NULL);
	ft_memset(p, 0, nmemb * size);
	return (p);
}

/*int main(void)
{
	int *arr = ft_calloc(5, sizeof(int));
	int i = 0;
	while (i < 5)
	{
		printf("%d ", arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/

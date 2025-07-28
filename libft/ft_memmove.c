/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:14:27 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/05 20:14:28 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	if ((size_t)dest - (size_t)src < n)
	{
		i = n - 1;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char src[] = "OverlapTest";
	char dest[20];

	ft_memmove(dest, src, strlen(src) + 1);
	printf("Non-overlapping test:\nSource: %s\nDestination: %s\n\n", src, dest);

	ft_memmove(src + 2, src, strlen(src) - 1);
	printf("Overlapping test (src before dest):\nSource: %s\n", src);

	return (0);
}*/

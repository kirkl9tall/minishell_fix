/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:40:06 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 16:22:59 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*p;
	const char	*k;

	i = 0;
	p = dest;
	k = src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		p[i] = k[i];
		i++;
	}
	return (dest);
}

/*#include <stdio.h>

int	main(void)
{
	char src[] = "Hello, World!";
	char dest[20];

	ft_memcpy(dest, src, 13);
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dest);
	return (0);
}*/

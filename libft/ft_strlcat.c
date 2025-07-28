/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:08:24 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/08 09:58:01 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dest_len;
	unsigned int	src_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (size == 0 || size <= dest_len)
		return (size + src_len);
	while (src[i] && i < size - dest_len - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/*#include <stdio.h>

int	main(void)
{
	char dst[20] = "Hello, ";
	const char *src = "world!";
	size_t size = 15;

	printf("Before: %s\n", dst);
	size_t result = ft_strlcat(dst, src, size);
	printf("After: %s\n", dst);
	printf("Total length: %zu\n", result);

	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:50:34 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/08 10:00:14 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
	{
		return (src_len);
	}
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/*#include <stdio.h>

int	main(void)
{
	char src[] = "Hello, world!";
	char dst[20];
	size_t len;

	len = ft_strlcpy(dst, src, sizeof(dst));
	printf("Copied string: %s\n", dst);
	printf("Source length: %zu\n", len);

	return (0);
}*/

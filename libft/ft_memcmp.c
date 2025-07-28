/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:37:32 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 16:22:32 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s_1;
	unsigned char	*s_2;
	unsigned char	c_1;
	unsigned char	c_2;

	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (s_1[i] == s_2[i] && i < n - 1)
		i++;
	c_1 = s_1[i];
	c_2 = s_2[i];
	return (c_1 - c_2);
}

/*#include <stdio.h>

int	main(void)
{
	char str1[] = "Hello";
	char str2[] = "HelloWorld";
	int result = ft_memcmp(str1, str2, 5);

	printf("Result: %d\n", result);
	return (0);
}*/

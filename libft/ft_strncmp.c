/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:09:53 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/23 23:30:11 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c_1;
	unsigned char	c_2;

	if (!s1 || !s2)
		return (1);
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] && s1[i] == s2[i])
		i++;
	c_1 = (unsigned char)s1[i];
	c_2 = (unsigned char)s2[i];
	return (c_1 - c_2);
}

/*#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_strncmp("hello", "hello", 3));
	printf("%d\n", ft_strncmp("hello", "hellz", 5));
	printf("%d\n", ft_strncmp("hello", "hella", 5));
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:03:04 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/12 21:44:05 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*#include <stdio.h>
#include <string.h>

int	main(void)
{
	char buffer[50] = "This is a test buffer.";

	ft_memset(buffer, 'k', 8);
	printf("Buffer after ft_memset: %s\n", buffer);

	return (0);
}*/

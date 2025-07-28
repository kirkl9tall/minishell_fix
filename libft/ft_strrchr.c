/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:21:05 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 20:59:10 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	c_1;

	len = ft_strlen(s);
	c_1 = (unsigned char)c;
	while (len >= 0)
	{
		if (s[len] == c_1)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void) {
	char str[] = "Hello, world!";
	char *result = ft_strrchr(str, 'o');
	if (result) {
		printf("Last occurrence of 'o': %s\n", result);
	} else {
		printf("'o' not found\n");
	}
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:13:24 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 21:05:48 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	p = malloc(ft_strlen(s) + 1);
    gr_t(p , 0);
	// if (!p)
	// 	return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*#include <stdio.h>

char	example_func(unsigned int i, char c)
{
	return (c + i);
}

int	main(void)
{
	char	str[] = "abc";
	char	*result;

	result = ft_strmapi(str, example_func);
	if (result)
	{
		printf("Result: %s\n", result);
		free(result);
	}
	return (0);
}
*/

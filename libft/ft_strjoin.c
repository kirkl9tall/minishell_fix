/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:59:01 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/31 10:55:55 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	gr_t(p, 0);
	if (!p)
		return (NULL);
	i = 0;
	if (ft_strlen(s1))
	{
		while (*s1)
			p[i++] = *s1++;
	}
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

/*#include <stdio.h>
int	main(void)
{
	char *str1 = "Hello, ";
	char *str2 = "42!";
	char *result = ft_strjoin(str1, str2);
	if (result)
	{
		printf("%s\n", result);
		free(result);
	}
	return (0);
}*/

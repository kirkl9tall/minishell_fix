/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:48:00 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/31 10:55:51 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*p;

	if (!s)
		return (NULL);
	i = 0;
	p = malloc((ft_strlen(s) + 1) * sizeof(char));
	gr_t(p, 0);
	if (p == NULL)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*#include<stdio.h>
int	main(void)
{
	char *str = "Hello, 42!";
	char *copy = ft_strdup(str);
	if (copy)
	{
		printf("Original: %s\n", str);
		printf("Copy: %s\n", copy);
		free(copy);
	}
	return (0);
}*/

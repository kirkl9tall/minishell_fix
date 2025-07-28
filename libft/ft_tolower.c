/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:37:33 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/08 10:20:02 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	char	c;
	char	result;

	c = 'A';
	result = ft_tolower(c);
	printf("Lowercase: %c\n", result);
	return (0);
}
*/
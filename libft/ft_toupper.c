/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:38:45 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/08 10:31:21 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
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

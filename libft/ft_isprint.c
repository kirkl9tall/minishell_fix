/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:49:53 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/05 18:49:55 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*int main(void)
{
	printf("%d\n", ft_isprint('A'));  // Expected: 1
	printf("%d\n", ft_isprint(' '));  // Expected: 1
	printf("%d\n", ft_isprint(31));
	return (0);
}*/
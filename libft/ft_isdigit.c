/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:46:44 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/05 18:46:47 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*int main(void)
{
	printf("%d\n", ft_isdigit('5'));  // Expected: 1
	printf("%d\n", ft_isdigit('a'));  // Expected: 0
	return (0);
}*/

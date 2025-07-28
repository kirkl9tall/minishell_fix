/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:41:25 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/05 18:41:26 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int		i;
	char	*p;

	i = 0;
	p = s;
	while (n--)
	{
		p[i] = 0;
		i++;
	}
}

/*int main(void)
{
	char str[] = "Hello, World!";

	ft_bzero(str, 5);
	printf("After ft_bzero: %s\n", str);

	return (0);
}*/

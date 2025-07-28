/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:23:57 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/12 22:04:21 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static void	ft_converter(char *str, int len, long num)
{
	while (num > 0)
	{
		str[len] = 48 + (num % 10);
		num /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	long	i;
	char	*p;
	long	n_len;

	n_len = ft_nbrlen(n);
	i = n;
	p = malloc((n_len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[n_len] = '\0';
	if (i == 0)
	{
		p[0] = '0';
		return (p);
	}
	if (i < 0)
	{
		p[0] = '-';
		i = -i;
	}
	n_len -= 1;
	ft_converter(p, n_len, i);
	return (p);
}

/*int main(void)
{
	printf("%s\n", ft_itoa(42));
	printf("%s\n", ft_itoa(-42));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(123456));
	printf("%s\n", ft_itoa(-2147483648));
}*/

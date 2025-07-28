/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:09:03 by a-khairi          #+#    #+#             */
/*   Updated: 2024/11/09 21:19:17 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sn;
	int	rest;

	sn = 1;
	rest = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sn = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rest = rest * 10 + (str[i] - '0');
		i++;
	}
	return (rest * sn);
}

/*int main(void)
{
	char *str1 = "   -12345";
	char *str2 = "42";
	char *str3 = "   +5678";
	char *str4 = "   -42abc";

	printf("Test 1: %d\n", ft_atoi(str1));
	printf("Test 2: %d\n", ft_atoi(str2));
	printf("Test 3: %d\n", ft_atoi(str3));
	printf("Test 4: %d\n", ft_atoi(str4));

	return (0);
}*/

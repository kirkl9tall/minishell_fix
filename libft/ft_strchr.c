/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:46:11 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 11:08:28 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c_1;

	if (!s)
		return (NULL);
	i = 0;
	c_1 = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == c_1)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == c_1)
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

/*int main(void)
{
	printf("%s\n", ft_strchr("Hello, 42!", 'o'));
	printf("%s\n", ft_strchr("Hello, 42!", 'z'));
	printf("%s\n", ft_strchr("Hello, 42!", '\0'));
	return (0);
}*/

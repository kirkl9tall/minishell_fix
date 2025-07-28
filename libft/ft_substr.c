/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:35:35 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 11:11:54 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	p = malloc(sizeof(char) * (len + 1));
	gr_t(p, 0);
	if (!p)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

/*int main()
{
	char str[] = "Hello, World!";
	char *substr = ft_substr(str, 7, 5);
  printf ("%s",substr);
  if (substr)
		free(substr);
	return (0);
}*/
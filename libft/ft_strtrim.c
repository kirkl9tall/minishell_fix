/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:32:59 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 21:06:01 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	i;
	unsigned int	len;
	char			*p;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	while (len > i && ft_strchr(set, s1[len - 1]))
		len--;
	p = (char *)malloc(len - i + 1);
    gr_t(p , 0);
	// if (!p)
	// 	return (NULL);
	ft_strlcpy(p, &s1[i], len - i + 1);
	return (p);
}

/*#include <stdio.h>

int	main(void)
{
	char	*trimmed;

	trimmed = ft_strtrim("  Hello World  ", " ");
	printf("%s\n", trimmed);
	free(trimmed);
	return (0);
}
*/

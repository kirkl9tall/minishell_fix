/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:15:31 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/04 11:42:02 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_strdup1(const char *str, int start, int end)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(end - start + 1);
	gr_t(copy, 0);
	while (start < end)
		copy[i++] = str[start++];
	copy[i] = '\0';
	return (copy);
}

static void	free_split(char **arr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**free_malloc(char **tab, char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	int		start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			len = 0;
			while (s[i + len] && s[i + len] != c)
				len++;
			tab[j] = ft_strdup1(s, start, start + len);
			if (!tab[j])
				return (free_split(tab, j), NULL);
			j++;
			i += len;
		}
	}
	return (tab);
}

char	**ft_split(const char *str, char c)
{
	char	**p;
	int		size;

	if (!str)
		return (NULL);
	size = (count_word(str, c) + 1);
	p = malloc(sizeof(char *) * size);
	gr_t(p, 0);
	p[size - 1] = NULL;
	free_malloc(p, str, c);
	return (p);
}

/*#include <stdio.h>
int	main(void)
{
	char	**result;
	int		i = 0;
	char	*str = "qwrt-yuiopffg-000=lkk]067  2267]\\u\\\\--\\\\oiyt";

	result = ft_split(str, '-');

	while (result[i])
	{
		printf("Word %d: %s\n", i + 1, result[i]);
		free(result[i]);
		i++;
	}
	free(result);

	return (0);
}*/
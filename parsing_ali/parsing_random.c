/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_random.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:34:21 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:33:02 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_buffer(int fd, char *buffer)
{
	if (read(fd, buffer, 200) <= 0)
		return (0);
	return (1);
}

static int	fill_random_string(char *str, int fd, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!fill_buffer(fd, buffer))
		return (0);
	while (j < 19)
	{
		if (i >= 200)
		{
			if (!fill_buffer(fd, buffer))
				return (0);
			i = 0;
		}
		if (ft_isalnum((unsigned char)buffer[i]))
			str[j++] = buffer[i];
		i++;
	}
	str[j] = '\0';
	return (1);
}

char	*randomize(void)
{
	char	buffer[200];
	char	*str;
	int		fd;

	str = malloc(20);
	gr_t(str, 0);
	if (!str)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (!fill_random_string(str, fd, buffer))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (str);
}

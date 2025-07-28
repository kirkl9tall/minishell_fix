/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_py_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:02:49 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/23 22:44:39 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_part_to_res(t_split_data *data)
{
	int		len;
	char	*part;

	len = data->ptr - data->start;
	part = malloc(len + 1);
	gr_t(part, 0);
	if (!part)
		return (0);
	ft_strncpy(part, data->start, len);
	part[len] = '\0';
	data->res[*(data->count)] = part;
	(*(data->count))++;
	return (1);
}

static int	handle_realloc_if_needed(t_split_data *data)
{
	int	old;

	if (*(data->count) >= *(data->capacity))
	{
		old = *(data->capacity);
		*(data->capacity) *= 2;
		data->res = ft_realloc(data->res, old * sizeof(char *),
				*(data->capacity) * sizeof(char *));
		if (!data->res)
			return (0);
	}
	return (1);
}

static int	handle_remaining_part(t_split_data *data)
{
	if (*(data->start))
	{
		data->res[*(data->count)] = ft_strdup(data->start);
		if (!data->res[*(data->count)])
			return (0);
		(*(data->count))++;
	}
	return (1);
}

static int	loop_split(t_split_data *data)
{
	while (*(data->ptr))
	{
		if (ft_strncmp(data->ptr, data->sep, data->sep_len) == 0)
		{
			if (!add_part_to_res(data))
				return (0);
			if (!handle_realloc_if_needed(data))
				return (0);
			data->ptr += data->sep_len;
			data->start = data->ptr;
		}
		else
			data->ptr++;
	}
	return (1);
}

char	**split_by_custom_separator(const char *str, const char *sep,
		int *count, int *capacity)
{
	t_split_data	data;

	if (!sep || !str)
		return (NULL);
	if (*capacity == 0)
		*capacity = 2;
	*count = 0;
	data.res = malloc((*capacity + 1) * sizeof(char *));
	gr_t(data.res, 0);
	if (!data.res)
		return (NULL);
	data.start = str;
	data.ptr = str;
	data.count = count;
	data.capacity = capacity;
	data.sep_len = ft_strlen(sep);
	data.sep = sep;
	if (!loop_split(&data))
		return (NULL);
	if (!handle_remaining_part(&data))
		return (NULL);
	return (data.res);
}

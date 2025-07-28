/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_random_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:14:49 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/28 11:16:09 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_substring(const char *str, const char *sub)
{
	int		len;
	int		sublen;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	sublen = ft_strlen(sub);
	res = malloc(len + 1);
	gr_t(res, 0);
	if (!str || !sub || !res)
		return (NULL);
	while (str[i])
	{
		if (ft_strncmp(&str[i], sub, sublen) == 0)
			i += sublen;
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

static char	*merge_tokens_with_rnd2(t_split_data *data, t_random *rend,
		int count)
{
	char	*merged;
	char	*clean;
	char	*tmp;

	merged = ft_strdup("");
	while (data->i < count && ft_strstr(data->tokens[data->i], rend->rnd_2))
	{
		clean = remove_substring(data->tokens[data->i], rend->rnd_2);
		tmp = ft_strjoin(merged, clean);
		merged = tmp;
		data->i++;
	}
	return (merged);
}

static void	append_next_token_if_valid(t_split_data *data, char **merged,
		t_random *rend, int count)
{
	char	*tmp;

	if (data->i < count && data->tokens[data->i]
		&& !ft_strstr(data->tokens[data->i], rend->rnd_1))
	{
		tmp = ft_strjoin(*merged, data->tokens[data->i]);
		*merged = tmp;
		data->i++;
	}
}

char	**merge_tokens_if_rnd2(char **tokens, int *count, t_random *rend)
{
	t_split_data	data;
	char			*merged;

	if (!tokens || !rend || !rend->rnd_2)
		return (tokens);
	data.tokens = tokens;
	data.count = count;
	data.i = 0;
	data.j = 0;
	data.new_tokens = malloc((*count + 1) * sizeof(char *));
	gr_t(data.new_tokens, 0);
	if (!data.new_tokens)
		return (NULL);
	while (data.i < *count)
	{
		if (ft_strstr(data.tokens[data.i], rend->rnd_2))
		{
			merged = merge_tokens_with_rnd2(&data, rend, *count);
			append_next_token_if_valid(&data, &merged, rend, *count);
			data.new_tokens[data.j++] = merged;
		}
		else
			data.new_tokens[data.j++] = data.tokens[data.i++];
	}
	return (data.new_tokens[data.j] = NULL,*count = data.j, data.new_tokens);
}

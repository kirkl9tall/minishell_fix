/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:35:59 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/03 21:30:41 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_sep(const char *str, const char *sep, const char *sep_2)
{
	int	sep_len;
	int	i;

	if (!str || !sep)
		return (0);
	sep_len = ft_strlen(sep);
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], sep, sep_len) == 0
			&& ft_strncmp(&str[i + sep_len], sep_2, sep_len) == 0)
			return (1);
		if (ft_strncmp(&str[i], sep, sep_len) != 0)
			return (0);
		i += sep_len;
	}
	return (1);
}

static int	count_words_between_sep(const char *token, t_random *rend)
{
	int			sep_len;
	int			word_count;
	const char	*ptr;
	const char	*next_sep;

	if (!token || !rend || !rend->rnd_1)
		return (0);
	ptr = token;
	word_count = 0;
	sep_len = ft_strlen(rend->rnd_1);
	while (1)
	{
		next_sep = ft_strstr(ptr, rend->rnd_1);
		if (!next_sep)
			break ;
		if (next_sep > ptr && ft_strncmp(ptr, rend->rnd_2,
				ft_strlen(rend->rnd_2)) != 0)
			word_count++;
		ptr = next_sep + sep_len;
	}
	if (*ptr && ft_strncmp(ptr, rend->rnd_2, ft_strlen(rend->rnd_2)) != 0)
		word_count++;
	return (word_count >= 2);
}

int	check_ambiguous(char *token, t_random *rend, int *flag)
{
	if (!token || !rend)
		return (1);
	*flag = 0;
	if (!ft_strcmp(token, rend->rnd_2))
	{
		*flag = 1;
		return (0);
	}
	if (only_sep(token, rend->rnd_1, rend->rnd_2))
	{
		*flag = 1;
		return (0);
	}
	if (!ft_strstr(token, rend->rnd_1))
		return (0);
	if (count_words_between_sep(token, rend))
		*flag = 1;
	return (0);
}

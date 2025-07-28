/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:56 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:28:13 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

int	append_part(char **token, char *part)
{
	char	*tmp;

	if (!part)
		return (1);
	if (!(*token))
	{
		*token = part;
		return (0);
	}
	tmp = ft_strjoin(*token, part);
	if (!tmp)
	{
		*token = NULL;
		return (1);
	}
	*token = tmp;
	return (0);
}

int	join(char **token, char *part)
{
	char	*tmp;

	if (*token)
		tmp = ft_strjoin(*token, part);
	else
		tmp = ft_strdup(part);
	if (!tmp)
		return (1);
	*token = tmp;
	return (0);
}

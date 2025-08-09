/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:03:44 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/05 19:07:28 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pars_delimter(int *i, char *delim, char **token)
{
	int		start;
	int		len;
	char	*part;
	char	quote;

	quote = delim[*i];
	start = ++(*i);
	while (delim[*i] && delim[*i] != quote)
		(*i)++;
	len = *i - start;
	part = ft_substr(delim, start, len);
	if (!part)
		return (1);
	if (delim[*i] == quote)
		(*i)++;
	if (append_part(token, part))
		return (1);
	return (0);
}

static int	pars_delimter_1(int *i, char *delim, char **token)
{
	int		start;
	int		len;
	char	*part;

	start = *i;
	while (delim[*i] && delim[*i] != '"' && delim[*i] != '\'')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (0);
	part = ft_substr(delim, start, len);
	if (!part)
		return (1);
	if (append_part(token, part))
		return (1);
	return (0);
}

char	*remov_quotes_delimiter(char *delim, int *flag)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	*flag = 1;
	if (!delim)
		return (NULL);
	while (delim[i])
	{
		if (delim[i] == '"' || delim[i] == '\'')
		{
			*flag = 0;
			if (pars_delimter(&i, delim, &token))
				return (NULL);
		}
		else
		{
			if (pars_delimter_1(&i, delim, &token))
				return (NULL);
		}
	}
	return (token);
}
//---------------------------------------------//

static void	handle_quoted_delimter(char *line, int *i, char **token)
{
	char	quote;
	int		start;
	char	*delim;

	quote = line[*i];
	start = (*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	delim = ft_substr(line, start, (*i) - start);
	append_part(token, delim);
}

char	*get_delimiter(char *line, int *i)
{
	char	*token;

	token = NULL;
	skip_spaces(i, line);
	while (line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'' || line[*i] == '$')
			handle_quoted_delimter(line, i, &token);
		else
		{
			if (handle_plain_text_token(i, line, &token))
				return (NULL);
		}
		if (line[*i] == '\0' || line[*i] == ' ' || line[*i] == '\t'
			|| line[*i] == '\n' || line[*i] == '|' || line[*i] == '<'
			|| line[*i] == '>')
			break ;
	}
	return (ft_strdup(token));
}
//-------------------------------------------------------//
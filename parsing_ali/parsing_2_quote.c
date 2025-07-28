/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:20:39 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:31:24 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_plain_text_token(int *i, char *line, char **token)
{
	int		start;
	int		len;
	char	*part;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& line[*i] != '"' && line[*i] != '\'' && line[*i] != '$')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (0);
	part = ft_substr(line, start, len);
	if (!part)
		return (1);
	if (append_part(token, part))
		return (1);
	return (0);
}

static int	handle_dollar_case(int *i, t_shell *shell, char **token)
{
	char	*part;
	int		flag;

	flag = 1;
	part = expand_dollar_token(shell, i, token, &flag);
	if (!part || append_part(token, part))
		return (1);
	return (0);
}

static int	handle_single_or_double_quote(int *i, t_shell *shell, char **token)
{
	if (shell->line[*i] == '\'')
		return (handle_single_quote_content(i, shell, token));
	else if (shell->line[*i] == '"')
		return (handle_double_quote_content(i, shell, token));
	return (0);
}

static int	process_char(int *i, t_shell *shell, char **token)
{
	if (shell->line[*i] == '\'' || shell->line[*i] == '"')
		return (handle_single_or_double_quote(i, shell, token));
	else if (shell->line[*i] == '$')
		return (handle_dollar_case(i, shell, token));
	else
		return (handle_plain_text_token(i, shell->line, token));
}

char	*frist_quote_content(int *i, t_shell *shell, int *flag)
{
	char	*token;
	int		err;

	token = NULL;
	err = 0;
	shell->flag_ex = 0;
	while (shell->line[*i] && !isspace(shell->line[*i])
		&& shell->line[*i] != '|' && shell->line[*i] != '<'
		&& shell->line[*i] != '>')
	{
		err = process_char(i, shell, &token);
		if (err)
			break ;
	}
	if (err)
	{
		*flag = 1;
		return (NULL);
	}
	return (token);
}

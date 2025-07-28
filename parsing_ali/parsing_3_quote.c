/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:36:52 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:26:50 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quote_content(int *i, t_shell *shell, char **token)
{
	int		start;
	int		len;
	char	*part;

	if (error_quotes(shell->line))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		shell->exit_statut = 2 << 8;
		return (1);
	}
	start = ++(*i);
	while (shell->line[*i] && shell->line[*i] != '\'')
		(*i)++;
	len = *i - start;
	part = ft_substr(shell->line, start, len);
	if (!part)
		return (1);
	if (shell->line[*i] == '\'')
		(*i)++;
	if (append_part(token, part))
		return (1);
	return (0);
}

static int	handle_plain_text(int *i, t_shell *shell, char **token)
{
	int		start;
	char	*exp;

	start = *i;
	while (shell->line[*i] && shell->line[*i] != '"' && shell->line[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		exp = ft_substr(shell->line, start, *i - start);
		if (!exp || append_part(token, exp))
			return (1);
	}
	return (0);
}

static int	handle_dollar(int *i, t_shell *shell, char **token)
{
	char	*exp;
	int		flag;

	flag = 1;
	exp = varible_ex(shell, i, token, &flag);
	if (!exp)
		return (1);
	if (append_part(token, ft_strdup(exp)))
		return (1);
	return (0);
}

int	handle_dq_token_part(int *i, t_shell *shell, char **token)
{
	if (shell->line[*i] == '$')
		return (handle_dollar(i, shell, token));
	else
		return (handle_plain_text(i, shell, token));
}

int	handle_double_quote_content(int *i, t_shell *shell, char **token)
{
	char	*empty;

	if (error_quotes(shell->line))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		shell->exit_statut = 2 << 8;
		return (1);
	}
	(*i)++;
	if (shell->line[*i] == '"')
	{
		empty = ft_strdup("");
		if (!empty || append_part(token, empty))
			return (1);
		(*i)++;
		return (0);
	}
	while (shell->line[*i] && shell->line[*i] != '"')
		if (handle_dq_token_part(i, shell, token))
			return (1);
	if (shell->line[*i] == '"')
		(*i)++;
	return (0);
}

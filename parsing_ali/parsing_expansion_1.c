/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:22:21 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/31 12:19:47 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_var(t_shell *shell, int *i)
{
	if (!shell->line[*i] || (!ft_isalnum(shell->line[*i])
			&& shell->line[*i] != '_' && shell->line[*i] != '?'))
		return (ft_strdup("$"));
	if (shell->line[*i] == '?')
	{
		(*i)++;
		if (WIFEXITED(shell->exit_statut))
			return (ft_strdup(ft_itoa(WEXITSTATUS(shell->exit_statut))));
		else if (WIFSIGNALED(shell->exit_statut))
			return (ft_strdup(ft_itoa(128 + WTERMSIG(shell->exit_statut))));
	}
	return (NULL);
}

char	*get_env_return(t_shell *shell, int start, int len)
{
	char	*var;
	char	*value;

	var = ft_substr(shell->line, start, len);
	if (!var)
		return (NULL);
	value = ft_getenv(shell->env, var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*extract_var_part(t_shell *shell, int *i)
{
	char	*special;
	char	*part;
	int		start;
	int		len;

	(*i)++;
	special = handle_special_var(shell, i);
	if (special)
		return (special);
	start = *i;
	while (shell->line[*i] && (ft_isalnum(shell->line[*i])
			|| shell->line[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup(""));
	part = get_env_return(shell, start, len);
	return (part);
}

char	*varible_ex(t_shell *shell, int *i, char **token, int *flag)
{
	char	*part;
	int		k;

	part = extract_var_part(shell, i);
	k = *i;
	if (is_special_dollar_case(shell, i))
		return (shell->flag_ex = 1, part);
	if (is_empty_token_with_only_spaces(token, part, shell, k))
		return (*flag = 0, ft_strdup(""));
	if (is_null_token_with_empty_quotes(token, part, shell, k))
		return (*flag = 0, ft_strdup(""));
	if (is_fully_empty_case(token, part, shell, k))
		return (*flag = 0, part);
	return (part);
}

int	is_special_dollar_case(t_shell *shell, int *i)
{
	return (shell->line[*i] == '$' && !ft_isalnum(shell->line[*i + 1])
		&& shell->line[*i + 1] != '_' && shell->line[*i + 1] != '?');
}

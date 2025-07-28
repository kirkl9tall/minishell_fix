/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:29:05 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:45:14 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_env *env, const char *envi)
{
	int		len;
	t_env	*temp;

	if (!envi || !env)
		return (NULL);
	len = ft_strlen(envi) + 1;
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->env, envi, ft_strlen(envi)) == 0
			&& temp->env[ft_strlen(envi)] == '=')
			return (temp->env + len);
		temp = temp->next;
	}
	return (NULL);
}

int	is_empty_token_with_only_spaces(char **token, char *part, t_shell *shell,
		int k)
{
	return ((*token && (*token)[0] == '\0') && only_spaces(part)
		&& (shell->line[k] != '\'' && shell->line[k + 1] != '\'')
		&& (shell->line[k] != '"' && shell->line[k + 1] != '"'));
}

int	is_null_token_with_empty_quotes(char **token, char *part, t_shell *shell,
		int k)
{
	return ((!*token) && only_spaces(part) && ((shell->line[k] == '\''
				&& shell->line[k + 1] == '\'') || (shell->line[k] == '"'
				&& shell->line[k + 1] == '"')));
}

int	is_fully_empty_case(char **token, char *part, t_shell *shell, int k)
{
	return (part[0] == '\0' && (!*token || (*token && (*token)[0] == '\0'))
		&& ((shell->line[k] == '\'' && shell->line[k + 1] == '\'')
			|| (shell->line[k] == '"' && shell->line[k + 1] == '"') || (*token
				&& (*token)[0] == '\0')));
}

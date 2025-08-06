/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:27:56 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/04 11:49:44 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	t_shell	*shell;

	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell = var_ali();
	shell->exit_statut = 130;
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	only_spaces(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
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

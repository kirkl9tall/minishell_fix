/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1_pipe_and_redirection.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:16:57 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:31:01 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_redirections(char *line)
{
	if (line[0] == '>' && line[1] == '>')
		return (ft_strdup(">>"));
	else if (line[0] == '>')
		return (ft_strdup(">"));
	else if (line[0] == '<' && line[1] == '<')
		return (ft_strdup("<<"));
	else if (line[0] == '<')
		return (ft_strdup("<"));
	return (NULL);
}

static int	handle_heredoc_delimiter(int *i, t_shell *shell)
{
	char	*delim;

	delim = get_delimiter(shell->line, i);
	if (!delim)
		return (0);
	if (error_quotes(delim))
	{
		ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		shell->exit_statut = 2 << 8;
		return (1);
	}
	if (add_token_to_list(&shell->token_list, delim, 1, 0))
		return (1);
	return (0);
}

int	handle_redirection(int *i, t_shell *shell)
{
	char	*redir_token;
	int		len;

	redir_token = check_redirections(shell->line + *i);
	if (!redir_token)
		return (0);
	if (add_token_to_list(&shell->token_list, redir_token, 0, 0))
		return (1);
	len = ft_strlen(redir_token);
	*i += len;
	if (!ft_strcmp(redir_token, "<<"))
		return (handle_heredoc_delimiter(i, shell));
	return (0);
}

void	handle_pipe(int *i, t_shell *shell)
{
	char	*pipe_token;

	pipe_token = ft_strdup("|");
	if (!pipe_token)
		return ;
	if (add_token_to_list(&shell->token_list, pipe_token, 0, 0))
		return ;
	(*i)++;
}

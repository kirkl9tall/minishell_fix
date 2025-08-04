/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:25:20 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 15:14:27 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

int	pars_h_1(int *i, char *delim, char **token)
{
	int		start;
	int		len;
	char	*part;

	start = *i;
	while (delim[*i] && delim[*i] != '$')
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

char	*expand_herdoc(char *delim, t_shell *shell)
{
	int		i;
	char	*token;
	char	*expand;

	i = 0;
	token = NULL;
	if (!delim)
		return (NULL);
	while (delim[i])
	{
		if (delim[i] == '$')
		{
			expand = extract_var_part(shell, &i);
			if (append_part(&token, expand))
				return (NULL);
		}
		else
		{
			if (pars_h_1(&i, delim, &token))
				return (NULL);
		}
	}
	return (token);
}

void	child_heredoc_exec(t_shell *shell, t_command *analyser, t_redirect *tmp)
{
	char	*line;

	signal(SIGINT, signal_handler_here_doc);
	while (1)
	{
		line = readline("herdoc > ");
		if (!line)
		{
			write(2, "Warning : delimited by EOF\n", 27);
			break ;
		}
		if (ft_strcmp(line, tmp->delimiter) == 0)
			break ;
		shell->line = line;
		if (tmp->quotes == 1)
			write(analyser->fd_here, expand_herdoc(line, shell),
				ft_strlen(expand_herdoc(line, shell)));
		else
			write(analyser->fd_here, line, ft_strlen(line));
		write(analyser->fd_here, "\n", 1);
		free(line);
	}
	free(line);
	free_herdoc_child(shell);
}

int	type_three_heredoc(t_shell *shell, t_command *analyser, t_redirect *tmp)
{
	int	pid;

	analyser->fd_here = open(shell->rend.rnd_3, O_CREAT | O_WRONLY | O_TRUNC,
			0644);
	analyser->fd1_here = open(shell->rend.rnd_3, O_RDONLY);
	if (analyser->fd_here == -1 || analyser->fd1_here == -1)
		perror("");
	unlink(shell->rend.rnd_3);
	pid = fork();
	if (!pid)
		child_heredoc_exec(shell, analyser, tmp);
	if (analyser->fd_here > 0)
		close(analyser->fd_here);
	waitpid(pid, &shell->exit_statut, 0);
	if (WEXITSTATUS(shell->exit_statut) == 130)
	{
		return (1);
	}
	return (0);
}

int	check_heredoc(t_shell *shell)
{
	t_command	*analyser;
	t_redirect	*tmp;

	analyser = shell->cmd;
	analyser->fd1_here = -1;
	analyser->fd_here = -1;
	while (analyser)
	{
		tmp = analyser->redirects;
		while (tmp)
		{
			if (tmp->type == 3)
				if (type_three_heredoc(shell, analyser, tmp))
					return (1);
			tmp = tmp->next;
		}
		analyser = analyser->next;
	}
	return (0);
}

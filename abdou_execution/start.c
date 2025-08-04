/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:25:27 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 10:27:45 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

void	p_n_pipe(t_hp *s)
{
	if (s->p != -1)
		close(s->p);
	if (s->i < s->nb_cmd - 1)
	{
		close(s->pipe_fd[1]);
		s->p = s->pipe_fd[0];
	}
}

void	handle_pipes(t_shell *shell)
{
	t_hp		s;
	t_command	*cmd;

	cmd = shell->cmd;
	s.nb_cmd = pipe_nbr(cmd) + 1;
	s.pid = malloc(s.nb_cmd * sizeof(int));
	gr_t(s.pid, 0);
	s.i = 0;
	s.p = -1;
	while (s.i < s.nb_cmd && cmd)
	{
		if (s.i < s.nb_cmd - 1)
			pipe(s.pipe_fd);
		s.pid[s.i] = fork();
		if (!s.pid[s.i])
			child_pipe(shell, cmd, s);
		p_n_pipe(&s);
		s.i++;
		cmd = cmd->next;
	}
	wait_childs(shell, s);
}

void	close_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

int	fathers_command(t_shell *shell, t_command *cmd)
{
	int	nbr_pipe;

	nbr_pipe = pipe_nbr(shell->cmd);
	if (nbr_pipe == 0)
	{
		if (redirecter(shell, cmd) == 1)
		{
			close_fds();
			return (0);
		}
		dup2(cmd->fd_out, 1);
		dup2(cmd->fd_in, 0);
		if (check_func_buil(shell, cmd) == 1)
			return (0);
	}
	return (1);
}

int	start(t_shell *shell)
{
	int	f;

	init_fds(shell);
	signal(SIGINT, SIG_IGN);
	if (check_heredoc(shell))
		return (0);
	f = check_cmd(shell->cmd);
	if (!f)
	{
		close_fds();
		return (0);
	}
	if (!fathers_command(shell, shell->cmd))
		return (0);
	handle_pipes(shell);
	dup2(shell->cmd->fd_origin, 1);
	dup2(shell->cmd->fd_origin_in, 0);
	close(shell->cmd->fd_origin);
	close(shell->cmd->fd_origin_in);
	return (0);
}

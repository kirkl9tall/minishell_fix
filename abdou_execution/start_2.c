/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:25:24 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 22:17:58 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

void	signal_handler_here_doc(int sig)
{
	t_shell	*shell;

	(void)sig;
	shell = var_ali();
	close_fds();
	free_env(shell->env);
	write(1, "\n", 1);
	gr_t(NULL, 1);
	exit(130);
}

int	pipe_nbr(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i - 1);
}

void	child_pipe(t_shell *shell, t_command *cmd, t_hp s)
{
	cmd->fd_out = 1;
	cmd->fd_in = 0;
	if (shell->cmd->fd_origin > 2)
		close(shell->cmd->fd_origin);
	if (shell->cmd->fd_origin_in > 2)
		close(shell->cmd->fd_origin_in);
	cmd->fd_origin = 1;
	cmd->fd_origin_in = 0;
	if (s.i > 0)
	{
		dup2(s.p, 0);
		close(s.p);
	}
	if (s.i < s.nb_cmd - 1)
	{
		dup2(s.pipe_fd[1], 1);
		close(s.pipe_fd[1]);
		close(s.pipe_fd[0]);
	}
	s.pid = NULL;
	analyser_command(shell, cmd);
}

void	wait_childs(t_shell *shell, t_hp s)
{
	s.i = 0;
	while (s.i < s.nb_cmd)
	{
		waitpid(s.pid[s.i], &shell->exit_statut, 0);
		s.i++;
	}
	if (WIFSIGNALED(shell->exit_statut))
	{
		if (WTERMSIG(shell->exit_statut) == 2
			|| WTERMSIG(shell->exit_statut) == 3)
		{
			if (WTERMSIG(shell->exit_statut) == 3)
				write(1, "Quit", 4);
			write(1, "\n", 1);
		}
	}
	if (s.p != -1)
		close(s.p);
	s.pid = NULL;
}

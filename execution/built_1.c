/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:24:36 by abismail          #+#    #+#             */
/*   Updated: 2025/08/06 10:26:23 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void	check_more(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[0][i])
	{
		if (cmd->args[0][i] != '.')
			return ;
		i++;
	}
	exit_relat_permission(shell, cmd, 0);
}

void	free_herdoc_child(t_shell *shell)
{
	free_env(shell->env);
	gr_t(NULL, 1);
	close_fds();
	exit(0);
}

void	dup_close(t_command *cmd)
{
	dup2(cmd->fd_origin, 1);
	dup2(cmd->fd_origin_in, 0);
	close(cmd->fd_origin);
	close(cmd->fd_origin_in);
}

int	check_func_buil(t_shell *shell, t_command *cmd)
{
	if (shell->cmd->args == NULL)
		return (-1);
	if (shell->cmd->args[0] == NULL)
		return (-1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		e_en_vi_ha(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		chdiriha(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		echowiha(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		p_doublviha(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		exporting(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		unsetiha(shell, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		exit_function(shell, cmd);
	else
		return (0);
	dup_close(cmd);
	return (1);
}

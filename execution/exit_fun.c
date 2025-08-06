/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:25:09 by abismail          #+#    #+#             */
/*   Updated: 2025/08/06 10:48:02 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void	check_sign(t_shell *shell, t_command *cmd)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
			sign++;
		i++;
	}
	if (sign > 1)
		exit_numeric_required(cmd, shell);
	return ;
}

void	exit_number(t_shell *shell, t_command *cmd)
{
	t_ex_f	s;

	check_sign(shell, cmd);
	s = ft_atoi_exit(cmd->args[1]);
	shell->exit_statut = s.res;
	if (s.flag == 1)
	{
		ft_putstr_fd("numeric argument required\n", 2);
		close(shell->cmd->fd_origin);
		close(shell->cmd->fd_origin_in);
		free_env(shell->env);
		gr_t(NULL, 1);
		exit(2);
	}
	write(2, "exit\n", 5);
	close(shell->cmd->fd_origin);
	close(shell->cmd->fd_origin_in);
	free_env(shell->env);
	gr_t(NULL, 1);
	exit(shell->exit_statut);
}

void	exit_arg_three(t_shell *shell, t_command *cmd)
{
	int	j;
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j])
		{
			if (ft_isalpha(cmd->args[1][i]))
				exit_numeric_required(cmd, shell);
			j++;
		}
		i++;
	}
	ft_putstr_fd("too many arguments\n", 2);
	shell->exit_statut = 1 << 8;
}

void	exit_one_arg(t_shell *shell)
{
	if (!shell->cmd->next)
		write(2, "exit\n", 5);
	free_env(shell->env);
	gr_t(NULL, 1);
	if (WIFEXITED(shell->exit_statut))
		exit(WEXITSTATUS(shell->exit_statut));
	else if (WIFSIGNALED(shell->exit_statut))
		exit(128 + WTERMSIG(shell->exit_statut));
}

void	exit_function(t_shell *shell, t_command *cmd)
{
	int	i;

	close_fds();
	i = 0;
	if (size_counter(cmd->args) == 1)
		exit_one_arg(shell);
	else if (size_counter(cmd->args) == 2)
	{
		while (cmd->args[1][i])
		{
			if (ft_isalpha(cmd->args[1][i]))
				exit_numeric_required(cmd, shell);
			i++;
		}
		exit_number(shell, cmd);
	}
	exit_arg_three(shell, cmd);
}

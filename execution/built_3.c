/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:24:42 by abismail          #+#    #+#             */
/*   Updated: 2025/08/06 10:26:30 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void	exit_relat_permission(t_shell *shell, t_command *cmd,
		int flag_permission)
{
	char	*buff;

	if (flag_permission == 1)
	{
		buff = ft_strjoin(cmd->args[0], ": permission denied\n");
		ft_putstr_fd(buff, 2);
		close_fds();
		free_env(shell->env);
		gr_t(NULL, 1);
		exit(126);
	}
	else
	{
		buff = ft_strjoin(cmd->args[0], ": command not found\n");
		ft_putstr_fd(buff, 2);
		close_fds();
		free_env(shell->env);
		gr_t(NULL, 1);
		exit(127);
	}
}

void	exec_f_x_ok(t_command *cmd, char *axe)
{
	if (access(axe, X_OK) == 0)
	{
		close_fds();
		execve(axe, &cmd->args[0], cmd->conv_env);
	}
}

void	relative_path(t_shell *shell, t_command *cmd)
{
	t_relat	s;

	s.env_p = ft_getenv(shell->env, "PATH");
	if (!s.env_p)
		env_p_null(shell, cmd);
	s.path = ft_split(s.env_p, ':');
	s.i = 0;
	s.flag_permission = 0;
	s.relat = ft_strjoin("/", cmd->args[0]);
	while (s.path[s.i])
	{
		s.axe = ft_strjoin(s.path[s.i], s.relat);
		if (access(s.axe, F_OK) == 0)
		{
			exec_f_x_ok(cmd, s.axe);
			s.flag_permission = 1;
			s.i++;
			continue ;
		}
		else
			s.i++;
	}
	exit_relat_permission(shell, cmd, s.flag_permission);
}

int	check_directory(t_command *cmd)
{
	struct stat	buff;

	if (stat(cmd->args[0], &buff) == 0)
	{
		if (S_ISDIR(buff.st_mode))
		{
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(" : is a directory\n", 2);
			return (1);
		}
	}
	return (errno);
}

void	non_built_in(t_shell *shell, t_command *cmd)
{
	int	ret;

	absolut_path(shell, cmd);
	relative_path(shell, cmd);
	ret = check_directory(cmd);
	if (ret != 0 && ret != 2)
	{
		if (ret != 1)
			perror("minishell");
		free_env(shell->env);
		gr_t(NULL, 1);
		close_fds();
		exit(126);
	}
}

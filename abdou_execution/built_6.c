/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:24:55 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 10:24:56 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

void	cd_home(t_shell *shell, char *old_pwd)
{
	char	*home;

	home = ft_getenv(shell->env, "HOME");
	if (home)
	{
		chdir(home);
		maj_env(shell, old_pwd);
		return ;
	}
	else
	{
		ft_putstr_fd("cd: HOME Not set\n", 2);
		shell->exit_statut = 1 << 8;
		return ;
	}
}

void	chdiriha(t_shell *shell, t_command *cmd)
{
	char	*old_pwd;

	old_pwd = ft_getenv(shell->env, "PWD");
	if (size_counter(cmd->args) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		shell->exit_statut = 1 << 8;
		return ;
	}
	else if (size_counter(cmd->args) == 1)
		cd_home(shell, old_pwd);
	else
	{
		if (chdir(shell->cmd->args[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(shell->cmd->args[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			shell->exit_statut = 1 << 8;
			return ;
		}
		maj_env(shell, old_pwd);
	}
	return ;
}

void	echo_no_flag(t_command *cmd, int j, int fd)
{
	while (cmd->args[j])
	{
		ft_putstr_fd(cmd->args[j], fd);
		if (cmd->args[j + 1])
			write(fd, " ", 1);
		j++;
	}
	write(fd, "\n", 1);
}

void	echo_flag(t_command *cmd, int i, int fd)
{
	while (cmd->args[i])
	{
		if (cmd->args[i + 1])
		{
			ft_putstr_fd(cmd->args[i], fd);
			write(fd, " ", 1);
		}
		else
			ft_putstr_fd(cmd->args[i], fd);
		i++;
	}
}

int	flag_mini(char *args)
{
	int	i;
	int	breaker;

	i = 1;
	breaker = 0;
	while (args[i])
	{
		if (args[i] != 'n')
		{
			breaker = 1;
			break ;
		}
		i++;
	}
	return (breaker);
}

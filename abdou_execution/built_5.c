/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:24:52 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 10:24:53 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

void	printer_echo(t_command *cmd, int flag_exist, int j)
{
	if (!cmd->args[j])
		return ;
	if (flag_exist == 1)
		echo_flag(cmd, j, cmd->fd_out);
	else
		echo_no_flag(cmd, j, cmd->fd_out);
}

t_echo_f	flag_echo_mac(char *args, t_echo_f f)
{
	if (args[0] == '-' && args[1] == 'n')
	{
		f.breaker = flag_mini(args);
		if (f.breaker == 1)
			return (f);
		f.flag_exist = 1;
	}
	else
		f.breaker = 1;
	return (f);
}

void	echowiha(t_shell *shell, t_command *cmd)
{
	int			j;
	t_echo_f	f;

	j = 1;
	f.breaker = 0;
	f.flag_exist = 0;
	if (size_counter(cmd->args) == 1)
	{
		write(cmd->fd_out, "\n", 1);
		return ;
	}
	while (cmd->args[j])
	{
		f = flag_echo_mac(cmd->args[j], f);
		if (f.breaker == 1)
			break ;
		j++;
	}
	printer_echo(cmd, f.flag_exist, j);
	shell->exit_statut = 0;
}

int	ft_my_env(t_shell *shell, char *var)
{
	while (shell->env)
	{
		if (ft_getenv(shell->env, var))
			return (1);
		shell->env = shell->env->next;
	}
	return (0);
}

void	p_doublviha(t_shell *shell, t_command *cmd)
{
	char	*buff;
	char	*result;

	(void)shell;
	buff = getcwd(NULL, 0);
	if (!buff)
		return ;
	result = ft_strjoin(buff, "\n");
	ft_putstr_fd(result, cmd->fd_out);
	free(buff);
}

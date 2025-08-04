/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:24:49 by abismail          #+#    #+#             */
/*   Updated: 2025/08/04 10:24:50 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_ali/minishell.h"

char	*ft_find_env(t_env *env, const char *envi)
{
	int	len;

	if (!envi || !env)
		return (NULL);
	len = ft_strlen(envi) + 1;
	if (ft_strncmp(env->env, envi, ft_strlen(envi)) == 0
		&& ((env->env[ft_strlen(envi)] == '=') || !env->env[ft_strlen(envi)]))
		return (env->env + len);
	return (NULL);
}

int	first_elem_unset(t_shell *shell, t_command *cmd)
{
	t_env	*env;
	t_env	*trash;

	env = shell->env;
	if (ft_find_env(env, cmd->args[1]))
	{
		trash = env;
		shell->env = env->next;
		trash = NULL;
		return (1);
	}
	return (0);
}

void	unsetiha(t_shell *shell, t_command *cmd)
{
	t_env	*env;
	t_env	*trash;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (first_elem_unset(shell, cmd))
			continue ;
		env = shell->env;
		while (env)
		{
			if (ft_find_env(env->next, cmd->args[i]))
			{
				trash = env->next;
				env->next = trash->next;
				free(trash->env);
				free(trash);
				trash = NULL;
				break ;
			}
			env = env->next;
		}
		i++;
	}
}

int	red_two(t_shell *shell, t_command *cmd, t_redirect *analyser)
{
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	cmd->fd_in = open(analyser->filename, O_RDONLY);
	if (cmd->fd_in == -1)
	{
		ft_putstr_fd(analyser->filename, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		shell->exit_statut = 1 << 8;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:25:18 by abismail          #+#    #+#             */
/*   Updated: 2025/08/06 10:27:13 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

t_env	*new_node(char *content)
{
	t_env	*node;
	int		i;

	node = malloc(sizeof(t_env));
	i = ft_strlen(content);
	node->env = malloc(i + 1);
	gr_t(node->env, 0);
	node->env = ft_envdup(content);
	node->next = NULL;
	return (node);
}

void	add_exp(t_env **env, char *content)
{
	t_env	*last;
	t_env	*node;

	last = *env;
	last = last->next;
	while (last->next)
		last = last->next;
	node = new_node(content);
	last->next = node;
}

char	**sort_declar_env(t_env *env)
{
	char	**str;
	int		i;
	int		j;
	char	*t;

	i = 0;
	str = conv_envs(env);
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				t = str[j];
				str[j] = str[i];
				str[i] = t;
			}
			j++;
		}
		i++;
	}
	return (str);
}

void	print_export_declar(t_env *trav, int fd_out)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = sort_declar_env(trav);
	while (sorted[i])
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(sorted[i], fd_out);
		ft_putstr_fd("\n", fd_out);
		i++;
	}
}

void	error_export_valid_args(t_command *cmd)
{
	ft_putstr_fd("export: `", cmd->fd_out);
	ft_putstr_fd(cmd->args[2], cmd->fd_out);
	ft_putstr_fd("': not a valid identifier", cmd->fd_out);
	write(cmd->fd_out, "\n", 1);
}

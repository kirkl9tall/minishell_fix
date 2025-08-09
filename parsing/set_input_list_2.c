/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:40:02 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/05 13:12:17 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*create_redirect_node(char *file, int append, int *flag)
{
	t_redirect	*new;
	char		*delimter;

	new = malloc(sizeof(t_redirect));
	gr_t(new, 0);
	if (!new)
		return (NULL);
	if (append == 3)
	{
		delimter = remov_quotes_delimiter(file, &new->quotes);
		new->delimiter = delimter;
		new->filename = NULL;
	}
	else
	{
		new->filename = ft_strdup(file);
		new->delimiter = NULL;
	}
	if (append != 3 && !new->filename)
		return (NULL);
	new->flag = *flag;
	new->type = append;
	new->next = NULL;
	return (new);
}

static void	copy_args(char **new_args, char **old_args, int count, char *rnd)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (!ft_strcmp(old_args[j], rnd))
			new_args[j] = NULL;
		else
		{
			new_args[j] = ft_strdup(old_args[j]);
			if (!new_args[j])
				return ;
		}
		j++;
	}
}

void	set_args(t_command *cmd, char *arg, t_random *rend)
{
	int		count;
	char	**new_args;

	count = 0;
	while (cmd->args && cmd->args[count])
		count++;
	new_args = malloc(sizeof(char *) * (count + 2));
	gr_t(new_args, 0);
	if (!new_args)
		return ;
	copy_args(new_args, cmd->args, count, rend->rnd_1);
	if (!ft_strcmp(arg, rend->rnd_1))
		new_args[count] = NULL;
	else
	{
		new_args[count] = ft_strdup(arg);
		if (!new_args[count] && ft_strcmp(arg, rend->rnd_1))
			return ;
	}
	new_args[count + 1] = NULL;
	cmd->args = new_args;
}

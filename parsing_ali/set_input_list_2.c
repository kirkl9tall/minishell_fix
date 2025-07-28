/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_list_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:40:02 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/24 10:35:12 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//--------------------------------------------------------------//
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

static int	handle_non_quoted(char *line, int *i, char **token)
{
	int		start;
	char	*delim;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\n'
		&& line[*i] != '\t' && line[*i] != '\n' && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
		(*i)++;
	if (*i == start)
		return (0);
	delim = ft_substr(line, start, (*i) - start);
	append_part(token, delim);
	return (1);
}

char	*get_delimiter(char *line, int *i)
{
	char	*token;

	token = NULL;
	skip_spaces(i, line);
	while (line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'')
			handle_quoted_delimter(line, i, &token);
		else
		{
			if (!handle_non_quoted(line, i, &token))
				return (NULL);
		}
		if (line[*i] == '\0' || line[*i] == ' ' || line[*i] == '\t'
			|| line[*i] == '\n' || line[*i] == '|' || line[*i] == '<'
			|| line[*i] == '>')
			break ;
	}
	return (ft_strdup(token));
}

//--------------------------------------------------------------//
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
//--------------------------------------------------------------//
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_error.c.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:07:51 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/22 10:11:50 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_pipe(t_token_node *head)
{
	t_token_node	*curr;

	curr = head;
	if (!curr)
		return (0);
	while (curr)
	{
		if (curr->token && !ft_strcmp(curr->token, "|") && curr->type == 0)
		{
			if (!curr->next || (curr->next->token
					&& !ft_strcmp(curr->next->token, "|")
					&& curr->next->type == 0))
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	error_redirection(t_token_node *head)
{
	t_token_node	*curr;

	curr = head;
	while (curr)
	{
		if (curr->token && (!ft_strcmp(curr->token, ">")
				|| !ft_strcmp(curr->token, ">>") || !ft_strcmp(curr->token, "<")
				|| !ft_strcmp(curr->token, "<<")) && curr->type == 0)
		{
			if (!curr->next)
				return (1);
			if (curr->next->token && curr->next->type == 0
				&& (!ft_strcmp(curr->next->token, ">")
					|| !ft_strcmp(curr->next->token, ">>")
					|| !ft_strcmp(curr->next->token, "<")
					|| !ft_strcmp(curr->next->token, "<<")
					|| !ft_strcmp(curr->next->token, "|"))
				&& curr->next->amb != 1)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	error_quotes(char *line)
{
	int		i;
	char	open_quote;

	i = 0;
	if (!line)
		return (0);
	open_quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"'))
		{
			if (open_quote == 0)
				open_quote = line[i];
			else if (open_quote == line[i])
				open_quote = 0;
		}
		i++;
	}
	return (open_quote != 0);
}

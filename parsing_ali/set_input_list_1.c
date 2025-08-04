/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_list_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:24:40 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/03 21:48:34 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_output(t_redirect **redir_list, char *file, int append, int *flag)
{
	t_redirect	*new;
	t_redirect	*tmp;

	new = create_redirect_node(file, append, flag);
	if (!new)
		return ;
	if (*redir_list == NULL)
		*redir_list = new;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	gr_t(cmd, 0);
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->args = NULL;
	cmd->append = 0;
	cmd->next = NULL;
	return (cmd);
}

static void	parse_input_help(t_token_node *node, t_command *cmd, t_random *rend)
{
	if (node->type == 1)
	{
		set_args(cmd, node->token, rend);
	}
	else if (node->type == 0)
	{
		if (!node->next)
			return ;
		if (node->next->token && !ft_strcmp(node->next->token, rend->rnd_1))
		{
			node->next->token = ft_strdup("");
		}
		if (ft_strcmp(node->token, ">") == 0)
			set_output(&cmd->redirects, node->next->token, 0, &node->next->amb);
		else if (ft_strcmp(node->token, ">>") == 0)
			set_output(&cmd->redirects, node->next->token, 1, &node->next->amb);
		else if (ft_strcmp(node->token, "<") == 0)
			set_output(&cmd->redirects, node->next->token, 2, &node->next->amb);
		else if (ft_strcmp(node->token, "<<") == 0)
			set_output(&cmd->redirects, node->next->token, 3, &node->next->amb);
	}
}

t_token_node	*fill_command_from_tokens(t_token_node *curr, t_command *cmd,
		t_random *rend)
{
	while (curr && !(curr->type == 0 && !ft_strcmp(curr->token, "|")))
	{
		parse_input_help(curr, cmd, rend);
		if (curr->type == 0 && (!ft_strcmp(curr->token, ">")
				|| !ft_strcmp(curr->token, ">>") || !ft_strcmp(curr->token, "<")
				|| !ft_strcmp(curr->token, "<<")))
		{
			curr = curr->next;
			if (!curr)
				break ;
		}
		curr = curr->next;
	}
	if (curr && !ft_strcmp(curr->token, "|"))
		curr = curr->next;
	return (curr);
}

t_command	*parse_input_linkedlist(t_token_node *token_list, t_random *rend)
{
	t_command		*head;
	t_command		*cur;
	t_command		*cmd;
	t_token_node	*curr;

	head = NULL;
	cur = NULL;
	curr = token_list;
	while (curr)
	{
		cmd = create_command();
		if (!cmd)
			return (NULL);
		curr = fill_command_from_tokens(curr, cmd, rend);
		if (!head)
			head = cmd;
		else
			cur->next = cmd;
		cur = cmd;
	}
	return (head);
}

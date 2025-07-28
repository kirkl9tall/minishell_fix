/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:54:56 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/23 22:45:22 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
				i++;
		}
	}
	return (count);
}

void	skip_spaces(int *i, char *line)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'
			|| line[*i] == '\n'))
		(*i)++;
}

static t_token_node	*new_token_node(char *token, int type, int amb)
{
	t_token_node	*node;

	node = malloc(sizeof(t_token_node));
	gr_t(node, 0);
	if (!node)
		return (NULL);
	node->token = token;
	node->type = type;
	node->amb = amb;
	node->next = NULL;
	return (node);
}

int	add_token_to_list(t_token_node **head, char *token, int type, int amb)
{
	t_token_node	*new_node;
	t_token_node	*temp;

	new_node = new_token_node(token, type, amb);
	if (!new_node)
		return (1);
	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (0);
}

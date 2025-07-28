/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_resulth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:42:36 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/22 10:42:37 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirects(t_redirect *redir)
{
	int	i;

	i = 0;
	while (redir)
	{
		if (redir->type == 0)
			printf("Outfile: %s (append = 0) ambiguous redirect : %d \n",
				redir->filename, redir->flag);
		else if (redir->type == 1)
			printf("Outfile: %s (append = 1)  ambiguous redirect : %d \n",
				redir->filename, redir->flag);
		else if (redir->type == 2)
			printf("Infile: %s  ambiguous redirect  %d \n", redir->filename,
				redir->flag);
		else if (redir->type == 3)
			printf("Heredoc: [%s] ------------   expand_vaible [%d]\n",
				redir->delimiter, redir->quotes);
		else
			printf("Unknown redirection type: %d\n", redir->type);
		redir = redir->next;
		i++;
	}
	printf("i === %d", i);
}

void	print_command(t_command *cmd)
{
	int	i;

	i = 0;
	printf("------ Command ------\n");
	if (cmd->args)
	{
		printf("Args: ");
		while (cmd->args[i])
		{
			printf("[%s] ", cmd->args[i]);
			i++;
		}
		printf("\n");
	}
	if (cmd->redirects)
		print_redirects(cmd->redirects);
	printf("---------------------\n");
}

void	print_commands(t_command *head)
{
	t_command	*current;
	int			i;

	current = head;
	i = 1;
	while (current)
	{
		printf("\n=== Command #%d ===\n", i);
		print_command(current);
		current = current->next;
		i++;
	}
}

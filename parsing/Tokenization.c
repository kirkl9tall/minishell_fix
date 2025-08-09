/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:11 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/06 00:03:06 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dupenv(const char *s)
{
	int		i;
	char	*p;

	if (!s)
		return (NULL);
	i = 0;
	p = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

t_shell	*var_ali(void)
{
	static t_shell	shell;

	return (&shell);
}

t_env	*fill_env(char **envp)
{
	t_env	*head;
	t_env	*node;

	head = NULL;
	while (*envp)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (NULL);
		node->env = ft_dupenv(*envp);
		node->next = head;
		head = node;
		envp++;
	}
	return (head);
}

int	start_process(t_shell *shell)
{
	int	i;

	i = 0;
	skip_spaces(&i, shell->line);
	while (shell->line[i])
	{
		if (shell->line[i] && shell->line[i] != ' ' && shell->line[i] != '|'
			&& shell->line[i] != '<' && shell->line[i] != '>')
		{
			if (lexical(&i, shell))
				return (1);
		}
		else if (shell->line[i] == '|')
			handle_pipe(&i, shell);
		else if (shell->line[i] == '>' || shell->line[i] == '<')
		{
			if (handle_redirection(&i, shell))
				return (1);
		}
		else
			i++;
		skip_spaces(&i, shell->line);
	}
	return (0);
}

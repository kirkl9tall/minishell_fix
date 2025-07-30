/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:11 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/30 09:55:50 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		node->env = ft_strdup(*envp);
		node->next = head;
		head = node;
		envp++;
	}
	return (head);
}

int	check_token(t_shell *shell)
{
	int	i;

	i = 0;
	skip_spaces(&i, shell->line);
	while (shell->line[i])
	{
		if (shell->line[i] && shell->line[i] != ' ' && shell->line[i] != '|'
			&& shell->line[i] != '<' && shell->line[i] != '>')
		{
			if (handle_quotes(&i, shell))
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
void signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = var_ali();
	shell->env = fill_env(envp);
	(void)ac;
	(void)**av;
	shell->exit_statut = 0;
	shell->defau_sigc = signal(SIGINT, signal_handler);
	shell->defau_sigq = signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, signal_handler);
		shell->rend.rnd_1 = randomize();
		shell->rend.rnd_2 = randomize();
		shell->rend.rnd_3 = randomize();
		shell->rend.space = 0;
		shell->token_list = NULL;
		shell->line = readline("minishell$ ");
		if (!shell->line)
			break ;
		if (check_token(shell))
		{
			gr_t(NULL, 0);
			free(shell->line);
			continue ;
		}
		if (error_pipe(shell->token_list)
			|| error_redirection(shell->token_list))
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			gr_t(NULL, 0);
			free(shell->line);
			shell->exit_statut = 2 << 8;
			continue ;
		}
		shell->cmd = parse_input_linkedlist(shell->token_list, &shell->rend);
		// print_commands(shell->cmd);
		if (shell->cmd)
			start(shell);
		if (shell->line)
			add_history(shell->line);
		free(shell->line);
		// gr_t(NULL, 0);
	}
	return (0);
}

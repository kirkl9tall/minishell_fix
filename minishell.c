/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-khairi <a-khairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:00:34 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/06 10:51:10 by a-khairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/minishell.h"

void	set_rend(t_shell *shell)
{
	shell->rend.rnd_1 = randomize();
	shell->rend.rnd_2 = randomize();
	shell->rend.rnd_3 = randomize();
}

void	handle_input(t_shell *shell)
{
	shell->cmd = parse_input_linkedlist(shell->token_list, &shell->rend);
	if (shell->cmd)
		start(shell);
	if (shell->line && shell->line[0] != '\0')
		add_history(shell->line);
	shell->line = NULL;
}

void	continue_syntax(t_shell *shell)
{
	add_history(shell->line);
	ft_putstr_fd("syntax error near unexpected token\n", 2);
	gr_t(NULL, 1);
	shell->line = NULL;
	shell->exit_statut = 2 << 8;
}

void	loop_shell(t_shell *shell)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, signal_handler);
		set_rend(shell);
		shell->token_list = NULL;
		input = readline("minishell$ ");
		shell->line = ft_strdup(input);
		free(input);
		if (!shell->line)
			return (signal_handler_q(0));
		if (start_process(shell))
		{
			add_history(shell->line);
			gr_t(NULL, 1);
		}
		else if (error_pipe(shell->token_list)
			|| error_redirection(shell->token_list))
			continue_syntax(shell);
		else
			handle_input(shell);
	}
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
	loop_shell(shell);
	gr_t(NULL, 1);
	return (0);
}
// print_commands(shell->cmd);

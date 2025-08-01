/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:11 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/01 12:02:40 by abismail         ###   ########.fr       */
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
	t_shell *shell;
	
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell = var_ali();
	shell->exit_statut = 130;
}
void free_env(t_env *env)
{
	t_env *tmp;
	while(env)
	{
		tmp = env;
		env = env->next;
		free(tmp->env);
		free(tmp);
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
		{
			gr_t(NULL, 1);
			free_env(shell->env);
			break ;
		}
		if (check_token(shell))
		{
			gr_t(NULL, 1);
			free(shell->line);
			continue ;
		}
		if (error_pipe(shell->token_list)
			|| error_redirection(shell->token_list))
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			gr_t(NULL, 1);
			free(shell->line);
			shell->line = NULL;
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
		shell->line = NULL;
		// gr_t(NULL, 1);
	}
	return (0);
}

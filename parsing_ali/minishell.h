/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:25 by a-khairi          #+#    #+#             */
/*   Updated: 2025/08/04 11:33:38 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <limits.h>

/* ----------------------------- STRUCTS ----------------------------- */

typedef struct s_relat
{
	char	*env_p;
	char	**path;
	int		i;
	char	*relat;
	char	*axe;
	int		flag_permission;
}	t_relat;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_echo_f
{
	int	breaker;
	int	flag_exist;
}	t_echo_f;

typedef struct s_pip
{
	int	p[2];
}	t_pip;

typedef struct s_random_stri
{
	char	*rnd_1;
	char	*rnd_2;
	char	*rnd_3;
	int		space;
	int		flag;
}	t_random;

typedef struct s_split_data
{
	const char	*start;
	const char	*ptr;
	char		**res;
	int			*count;
	int			*capacity;
	int			sep_len;
	const char	*sep;
	int			i;
	int			j;
	char		**tokens;
	char		**new_tokens;
}	t_split_data;

typedef struct s_redirect
{
	int					type;
	char				*filename;
	char				*delimiter;
	int					quotes;
	int					flag;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}	t_env;

typedef struct s_hp
{
	int	i;
	int	p;
	int	pipe_fd[2];
	int	*pid;
	int	nb_cmd;
}	t_hp;

typedef struct s_command
{
	char				**args;
	t_redirect			*redirects;
	int					append;
	char				**conv_env;
	struct s_command	*next;
	int					fd_here;
	int					fd1_here;
	int					fd_out;
	int					fd_in;
	int					fd_origin;
	int					fd_origin_in;
}	t_command;

typedef struct s_token_node
{
	char				*token;
	int					type;
	int					amb;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_ex_f
{
	long	res;
	int		flag;
}	t_ex_f;

typedef struct s_shell
{
	t_command		*cmd;
	t_token_node	*token_list;
	t_random		rend;
	int				exit_statut;
	int				capacity;
	t_env			*env;
	char			*line;
	int				flag_ex;
	int				flag;
	t_pip			*ps;
	void			*defau_sigc;
	void			*defau_sigq;
}	t_shell;

/* ----------------------------- PROTOTYPES ----------------------------- */

int			error_pipe(t_token_node *head);
int			error_redirection(t_token_node *head);
int			error_quotes(char *line);

int			start_process(t_shell *shell);
int			lexical(int *i, t_shell *shell);
char		*analys_token(int *i, t_shell *shell, int *flag);
void		handle_pipe(int *i, t_shell *shell);
int			handle_redirection(int *i, t_shell *shell);
int			handle_plain_text_token(int *i, char *line, char **token);
int			append_part(char **token, char *part);
int			only_spaces(const char *s);
char		*varible_ex(t_shell *shell, int *i, char **token, int *flag);
char		*randomize(void);
int			check_ambiguous(char *token, t_random *rend, int *flag);
char		**split_by_custom_separator(
				const char *str,
				const char *sep,
				int *count,
				int *capacity);
char		**merge_tokens_if_rnd2(
				char **tokens,
				int *count,
				t_random *rend);
int			join(char **token, char *part);
int			handle_single_quote_content(int *i, t_shell *shell, char **token);
int			handle_double_quote_content(int *i, t_shell *shell, char **token);
int			handle_dq_token_part(int *i, t_shell *shell, char **token);
char		*replace_spaces_with_sep(const char *str, const char *sep);
char		*ft_getenv(t_env *env, const char *key);
void		add_back_env(t_env *env, char *var);
int			is_empty_token_with_only_spaces(
				char **token,
				char *part,
				t_shell *shell,
				int k);
int			is_fully_empty_case(
				char **token,
				char *part,
				t_shell *shell,
				int k);
int			is_null_token_with_empty_quotes(
				char **token,
				char *part,
				t_shell *shell,
				int k);
char		*expand_dollar_token(
				t_shell *shell,
				int *i,
				char **token,
				int *flag);
void		skip_spaces(int *i, char *line);
char		*remov_quotes_delimiter(char *delim, int *flag);
void		set_args(t_command *cmd, char *arg, t_random *rend);
void		handle_quoted_delimter(char *line, int *i, char **token);
char		*get_delimiter(char *line, int *i);
int			count_words(const char *str);
char		*extract_var_part(t_shell *shell, int *i);
int			add_token_to_list(
				t_token_node **head,
				char *token,
				int type,
				int amb);
t_redirect	*create_redirect_node(char *file, int append, int *flag);
void		gr_t(void *str, int flag);
t_env		*fill_env(char **envp);

t_command	*parse_input_linkedlist(
				t_token_node *token_list,
				t_random *rend);
int			ft_isspace(int c);

void		print_commands(t_command *head);

int			start(t_shell *shell);
void		analyser_command(t_shell *shell, t_command *cmd);
void		free_all(t_shell *shell);
t_shell		*var_ali(void);
int			check_heredoc(t_shell *shell);
char		*ft_find_env(t_env *env, const char *envi);
int			first_elem_unset(t_shell *shell, t_command *cmd);
void		unsetiha(t_shell *shell, t_command *cmd);
void		dup_close(t_command *cmd);
int			check_func_buil(t_shell *shell, t_command *cmd);
void		del_env(t_shell **cmd);
void		init_fds(t_shell *shell);
int			check_cmd(t_command *cmd);
void		analyse_check_dups(t_command *cmd);
void		absolut_path(t_shell *shell, t_command *cmd);
void		env_p_null(t_shell *shell, t_command *cmd);
void		exit_relat_permission(
				t_shell *shell,
				t_command *cmd,
				int flag_permission);
void		exec_f_x_ok(t_command *cmd, char *axe);
void		relative_path(t_shell *shell, t_command *cmd);
int			check_directory(t_command *cmd);
void		non_built_in(t_shell *shell, t_command *cmd);
int			red_two(t_shell *shell, t_command *cmd, t_redirect *analyser);
void		printer_echo(t_command *cmd, int flag_exist, int j);
t_echo_f	flag_echo_mac(char *args, t_echo_f f);
void		echowiha(t_shell *shell, t_command *cmd);
int			ft_my_env(t_shell *shell, char *var);
void		p_doublviha(t_shell *shell, t_command *cmd);
void		cd_home(t_shell *shell, char *old_pwd);
void		chdiriha(t_shell *shell, t_command *cmd);
void		echo_no_flag(t_command *cmd, int j, int fd);
void		echo_flag(t_command *cmd, int i, int fd);
int			flag_mini(char *args);
char		**conv_envs(t_env *env);
void		maj_pwd(t_shell *shell);
int			maj_env(t_shell *shell, char *old_pwd);
void		e_en_vi_ha(t_shell *shell, t_command *cmd);
int			size_counter(char **args);
int			red_one(t_shell *shell, t_command *cmd, t_redirect *analyser);
int			red_zero(t_shell *shell, t_command *cmd, t_redirect *analyser);
int			redirection_mode(
				t_shell *shell,
				t_command *cmd,
				t_redirect *analyser);
int			redirecter(t_shell *shell, t_command *cmd);
int			scan_len_env(t_env *scaner);
t_ex_f		ft_atoi_exit(const char *str);
void		exit_numeric_required(t_command *cmd, t_shell *shell);
void		exit_number(t_shell *shell, t_command *cmd);
void		exit_arg_three(t_shell *shell, t_command *cmd);
void		exit_function(t_shell *shell, t_command *cmd);
void		exporting(t_shell *shell, t_command *cmd);
int			env_similar(t_env *trav1, char *name, char *replace);
int			is_env_valid(char *args);
int			is_it_alpha_valid(t_shell *shell, t_command *cmd, int i);
int			contain_equal(char *args);
int			is_exist(t_env *env, const char *envi);
t_env		*new_node(char *content);
void		add_exp(t_env **env, char *content);
char		**sort_declar_env(t_env *env);
void		print_export_declar(t_env *trav, int fd_out);
void		error_export_valid_args(t_command *cmd);
int			pipe_nbr(t_command *cmd);
int			dupper(t_command *cmd);
void		signal_handler_child(void);
void		handle_pipes(t_shell *shell);
void		free_env(t_env *env);
void		close_fds(void);
char		*ft_envjoin(char *s1, char *s2);
char		*ft_envdup(const char *s);
void		signal_handler_here_doc(int sig);
int			pars_h_1(int *i, char *delim, char **token);
char		*expand_herdoc(char *delim, t_shell *shell);
void		child_heredoc_exec(
				t_shell *shell,
				t_command *analyser,
				t_redirect *tmp);
int			type_three_heredoc(
				t_shell *shell,
				t_command *analyser,
				t_redirect *tmp);
void		none_equal_case_export(
				t_shell *shell,
				t_command *cmd,
				int i,
				t_env *trav);
void		export_case_equal(
				t_shell *shell,
				t_command *cmd,
				int i,
				t_env *trav);
void		exit_one_arg(t_shell *shell);
void		check_sign(t_shell *shell, t_command *cmd);
void		permission_denied_path(t_shell *shell);
void		no_such_file(t_shell *shell);
void		check_analyser_troubles(t_shell *shell, t_command *cmd);
void		child_pipe(t_shell *shell, t_command *cmd, t_hp s);
void		wait_childs(t_shell *shell, t_hp s);
void		cleaner_heredoc(t_shell *shell);
#endif

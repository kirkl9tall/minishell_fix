/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:08:25 by a-khairi          #+#    #+#             */
/*   Updated: 2025/07/28 11:09:06 by abismail         ###   ########.fr       */
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
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

/* ----------------------------- STRUCTS ----------------------------- */
typedef struct s_relat
{
    char *env_p;
    char **path;
    int i;
    char * relat;
    char *axe;
    int flag_permission;

}t_relat;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_echo_f
{
    int breaker;
    int flag_exist;
}t_echo_f;

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
	int 				fd_origin_in;
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
	int res;
	int flag;
}t_ex_f;

typedef struct s_shell
{
    t_command           *cmd;
    t_token_node        *token_list;
    t_random            rend;
    int                 exit_statut;
    int                 capacity;
    t_env               *env;
    char                *line;
    int                 flag_ex;
    int                 flag;
	t_pip				*ps;
	void				*defau_sigc;
	void				*defau_sigq;
}   t_shell;

/* ----------------------------- ERROR ----------------------------- */

int			error_pipe(t_token_node *head);
int			error_redirection(t_token_node *head);
int			error_quotes(char *line);

/* ----------------------------- PARSING ----------------------------- */

int			handle_quotes(int *i, t_shell *shell);
char		*frist_quote_content(int *i, t_shell *shell, int *flag);
void		handle_pipe(int *i, t_shell *shell);
int			handle_redirection(int *i, t_shell *shell);
int			handle_plain_text_token(int *i, char *line, char **token);
int			append_part(char **token, char *part);
int			only_spaces(const char *s);
char		*varible_ex(t_shell *shell, int *i, char **token, int *flag);
char		*randomize(void);
int			check_ambiguous(char *token, t_random *rend, int *flag);
char		**split_by_custom_separator(const char *str, const char *sep,
				int *count, int *capacity);
char		**merge_tokens_if_rnd2(char **tokens, int *count,
				t_random *rend);
int			join(char **token, char *part);
int			handle_single_quote_content(int *i, t_shell *shell,
				char **token);
int			handle_double_quote_content(int *i, t_shell *shell,
				char **token);
int			handle_dq_token_part(int *i, t_shell *shell, char **token);
char		*replace_spaces_with_sep(const char *str, const char *sep);
char		*ft_getenv(t_env *env, const char *key);
void		add_back_env(t_env *env, char *var);
int			is_empty_token_with_only_spaces(char **token, char *part,
				t_shell *shell, int k);
int			is_fully_empty_case(char **token, char *part,
				t_shell *shell, int k);
int			is_null_token_with_empty_quotes(char **token, char *part,
				t_shell *shell, int k);
int			is_special_dollar_case(t_shell *shell, int *i);
char		*expand_dollar_token(t_shell *shell, int *i,
				char **token, int *flag);
void		skip_spaces(int *i, char *line);
char		*remov_quotes_delimiter(char *delim, int *flag);
void		set_args(t_command *cmd, char *arg, t_random *rend);
void		handle_quoted_delimter(char *line, int *i, char **token);
char		*get_delimiter(char *line, int *i);
int			count_words(const char *str);
char		*extract_var_part(t_shell *shell, int *i);
int			add_token_to_list(t_token_node **head,
				char *token, int type, int amb);
t_redirect	*create_redirect_node(char *file, int append, int *flag);
void		gr_t(void *str, int flag);

/* ----------------------------- SETUP ----------------------------- */

t_command	*parse_input_linkedlist(t_token_node *token_list,
				t_random *rend);

/* ----------------------------- DEBUG ----------------------------- */

void		print_commands(t_command *head);

/* ----------------------------- CORE ----------------------------- */
int start(t_shell *shell);
void analyser_command (t_shell *shell,t_command *cmd);
void free_all(t_shell *shell);
t_shell *var_ali(void);

#endif

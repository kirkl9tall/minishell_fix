#include "parsing_ali/minishell.h"

t_ex_f	ft_atoi_exit(const char *str)
{
	int	i;
	int	sn;
	t_ex_f res;

	sn = 1;
	res.res = 0;
    res.flag = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sn = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res.res = res.res * 10 + (str[i] - '0');
		if (res.res > INT_MAX   || res.res < INT_MIN)
			res.flag = 1;
        i++;
	}
	res.res = res.res *sn;
	return (res);
}

void exit_numeric_required (t_command *cmd,t_shell *shell)
{
    ft_putstr_fd("exit\n",2);
    ft_putstr_fd(cmd->args[0],2);
    ft_putstr_fd(" : ",2);
    ft_putstr_fd(cmd->args[1],2);
    ft_putstr_fd(" : numeric argument required\n",2);
    close(shell->cmd->fd_origin);
    close(shell->cmd->fd_origin_in);
    free_env(shell->env);
    gr_t(NULL,1);
    exit(2);
}
void check_sign(t_shell *shell,t_command *cmd)
{
    int i;
    int sign;
    i = 0;
    sign = 0;
    while (cmd->args[1][i])
    {
        if (!ft_isdigit(cmd->args[1][i]))
            sign++;
        i++;
    }
    if (sign > 1)
      exit_numeric_required(cmd,shell);
    return;  
}
void exit_number(t_shell *shell,t_command *cmd)
{
    t_ex_f s;

    check_sign(shell,cmd);
    s = ft_atoi_exit(cmd->args[1]);
    shell->exit_statut = s.res;
    if (s.flag == 1)
    {
        ft_putstr_fd("numeric argument required\n",2);
        close(shell->cmd->fd_origin);
        close(shell->cmd->fd_origin_in);
        free_env(shell->env);
        gr_t(NULL,1);
        exit (2);
    }
    write (2,"exit\n",5);
    close(shell->cmd->fd_origin);
    close(shell->cmd->fd_origin_in);
    free_env(shell->env);
    gr_t(NULL,1);
    exit(shell->exit_statut);
}

void exit_arg_three(t_shell *shell , t_command *cmd)
{  
    int j;
    int i;

    i = 0;
    while (cmd->args[i])
    {
        j = 0;
        while (cmd->args[i][j])
        {
            if (ft_isalpha(cmd->args[1][i]))
                exit_numeric_required(cmd,shell);
            j++;
        }
        i++;
    }
    ft_putstr_fd("too many arguments\n",2);
    shell->exit_statut = 1 << 8;
}

void exit_one_arg (t_shell *shell)
{
    write (2,"exit\n",5);
    free_env(shell->env);
    gr_t(NULL,1);
    if (WIFEXITED(shell->exit_statut))
        exit(WEXITSTATUS(shell->exit_statut));
    else if (WIFSIGNALED(shell->exit_statut))
        exit (128 + WTERMSIG(shell->exit_statut));
}
void exit_function(t_shell *shell , t_command *cmd)
{
    int i;

    close_fds();
    i = 0;
    if (size_counter(cmd->args) == 1)
        exit_one_arg(shell);
    else if (size_counter(cmd->args) == 2)
    {
        while (cmd->args[1][i])
        {
            if (ft_isalpha(cmd->args[1][i]))
                exit_numeric_required(cmd,shell);
            i++;
        }
        exit_number(shell,cmd);
    }
    exit_arg_three(shell,cmd);
}
#include "parsing_ali/minishell.h"


void del_env(t_shell **cmd)
{
    t_shell *plo;
    t_env  *trash;
    plo = *cmd;
    trash = plo->env->next;
    plo->env->next = plo->env->next->next;
    free(trash);
}

void init_fds(t_shell * shell)
{
    shell->cmd->fd_origin = dup(1);
    shell->cmd->fd_origin_in = dup(0);
    shell->cmd->fd_out = 1;
    shell->cmd->fd_in = 0;
}
int check_cmd(t_command *cmd)
{
    t_command * trav;
    int i = 0;
    trav = cmd;
    while (trav)
    {
        if (trav->args)
            i++;
        trav = trav->next;
    }
    if (cmd->redirects)
    {
        while (cmd->redirects)
        {
            if (cmd->redirects->type != 3)
                i++;
            cmd->redirects = cmd->redirects->next;
        }
    }
    return i ;
}

void analyser_command (t_shell *shell,t_command *cmd)
{
    signal(SIGINT, shell->defau_sigc);
    signal(SIGQUIT, shell->defau_sigq);
    cmd->fd_out = 1;
    cmd->fd_in = 0;
    if (redirecter(shell,cmd) == 1)
        exit(1);
         if (!cmd->args)
        exit(0);
    if (!cmd->args[0][0])
    {
        write(2, "Command not found\n", 18);
        exit(0);
    }
    analyse_check_dups(cmd);
    if (check_func_buil(shell,cmd) == 1)
        exit(shell->exit_statut >> 8);
    cmd->conv_env = conv_envs(shell->env);
    non_built_in(shell,cmd);
}

void analyse_check_dups(t_command * cmd)
{
 if (cmd->fd_out > 1)
    {
        dup2(cmd->fd_out,1);
        close (cmd->fd_out);
        cmd->fd_out = 1;
    }
    if (cmd->fd_in > 0)
    {
        dup2(cmd->fd_in,0);
        close (cmd->fd_in);
        cmd->fd_in = 0;
    }
}
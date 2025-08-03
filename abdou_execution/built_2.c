#include "parsing_ali/minishell.h"


void del_env(t_shell **cmd)
{
    t_shell *plo;
    t_env  *trash;
    plo = *cmd;
    trash = plo->env->next;
    plo->env->next = plo->env->next->next;
    // free(trash);
    trash = NULL;
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
    t_redirect *redirects;
    
    redirects = cmd->redirects;
    int i = 0;
    trav = cmd;
    while (trav)
    {
        if (trav->args)
            i++;
        trav = trav->next;
    }
    if (redirects)
    {
        while (redirects)
        {
            if (redirects->type != 3)
                i++;
            redirects = redirects->next;
        }
    }
    return i ;
}
void check_analyser_troubles(t_shell *shell,t_command *cmd)
{
    if (redirecter(shell,cmd) == 1)
    {
        close_fds();
        exit(1);
    }
    if (!cmd->args || !cmd->args[0])
    {
        gr_t(NULL , 1);
        close_fds();
        exit(0);
    }
    if (!cmd->args[0][0])
    {
        free_env(shell->env);
        gr_t(NULL , 1);
        close_fds();
        write(2, "Command not found\n", 18);
        exit(127);
    }   
}
void analyser_command (t_shell *shell,t_command *cmd)
{
    signal(SIGINT, shell->defau_sigc);
    signal(SIGQUIT, shell->defau_sigq);
    cmd->fd_out = 1;
    cmd->fd_in = 0;
    check_analyser_troubles(shell,cmd);
    analyse_check_dups(cmd);
    if (check_func_buil(shell,cmd) == 1)
    {
        free_env(shell->env);
        shell->env = NULL;
        close_fds();
        gr_t(NULL , 1);
        exit(shell->exit_statut >> 8);
    }
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
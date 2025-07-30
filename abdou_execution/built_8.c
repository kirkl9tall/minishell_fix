#include "parsing_ali/minishell.h"

int red_one(t_shell * shell ,t_command *cmd, t_redirect * analyser)
{
    cmd->fd_out = open(analyser->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
    if (cmd->fd_out == -1)
    {
        ft_putstr_fd(" Permission denied\n",2);
        shell->exit_statut = 1 << 8;
        return (1);
    }
    return (0);  
}

int red_zero(t_shell * shell ,t_command *cmd, t_redirect * analyser)
{
    cmd->fd_out = open(analyser->filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
    if (cmd->fd_out == -1)
    {
        ft_putstr_fd(" Permission denied\n",2);
        shell->exit_statut = 1 << 8;
        return (1);
    }
    return (0);
}

int redirection_mode (t_shell * shell ,t_command *cmd, t_redirect * analyser)
{
    if (analyser->flag == 1)
    {
        ft_putstr_fd("minishell: ambiguous redirect\n",2);
        shell->exit_statut = 1 << 8;
        return(1);
    }
    else if (analyser->type == 0)
    {
        if (red_zero(shell,cmd,analyser) == 1)
            return (1);
    }
    else if (analyser->type == 1)
    {
        if (red_one(shell,cmd,analyser) == 1)
            return (1);           
    }
    else if (analyser->type == 2)
    {
        if (red_two(shell,cmd,analyser) == 1)
            return (1);
    }
    else if (analyser->type == 3) 
    {
        cmd->fd_in =  dup(cmd->fd1_here);  
        close (cmd->fd1_here);
    }
    return (0);
}

int redirecter (t_shell *shell , t_command *cmd)
{
    t_redirect *analyser;

    analyser = cmd->redirects;
    if (analyser)
    {            

        while (analyser)
        {
            if (redirection_mode (shell,cmd,analyser) == 1)
                return (1);
            analyser = analyser->next;
        }
    }
    return  0;
}

int  scan_len_env (t_env *scaner)
{
    int i;
    i = 0;

    while(scaner)
    {
        i++;
        scaner = scaner->next;
    }
    return i; 
}

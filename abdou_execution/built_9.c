#include "parsing_ali/minishell.h"

void del_env(t_shell **cmd)
{
    t_shell *plo;
    t_env  *trash;
    plo = *cmd;
    trash = plo->env->next;
    plo->env->next = plo->env->next->next;
    trash = NULL;
}
void permission_denied_path(t_shell * shell)
{
    ft_putstr_fd("Permission denied\n",2);
    free_env(shell->env);
    close_fds();
    gr_t(NULL,1);
    exit(126); 

}
void no_such_file(t_shell * shell)
{
    ft_putstr_fd("No such file or directory\n",2);
    free_env(shell->env);
    close_fds();
    gr_t(NULL,1);
    exit (127);

}
void absolut_path(t_shell *shell ,t_command * cmd)
{
    if  (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
    {
         if (access(cmd->args[0],F_OK) == 0)
        {
            if (access(cmd->args[0],X_OK)== 0)
            {
                close_fds();
                execve(cmd->args[0],&cmd->args[0],cmd->conv_env);
            }
            else
                permission_denied_path(shell);
        }
        else
            no_such_file(shell);
    }
}

void env_p_null(t_shell *shell, t_command * cmd)
{
    if (access(cmd->args[0],F_OK) == 0)
        {
            if (access(cmd->args[0],X_OK)== 0)
            {
                close_fds();
                execve(cmd->args[0],&cmd->args[0],cmd->conv_env);
            }
            else
                permission_denied_path(shell);
        }
        else
            no_such_file(shell);
}
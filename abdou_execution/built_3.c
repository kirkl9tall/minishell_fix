#include "parsing_ali/minishell.h"

void absolut_path(t_shell *shell ,t_command * cmd)
{
    if  (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
    {
         if (access(cmd->args[0],F_OK) == 0)
        {
            if (access(cmd->args[0],X_OK)== 0)
                execve(cmd->args[0],&cmd->args[0],cmd->conv_env);
            else
            {
                ft_putstr_fd("Permission denied\n",2);
                exit(126); //exit status 
                free_env(shell->env);
                gr_t(NULL,1);
            }
        }
        else
        {
            ft_putstr_fd("No such file or directory\n",2);
            free_env(shell->env);
            gr_t(NULL,1);
            exit (127); //// exit status 
        }
    }
}

void env_p_null (t_shell *shell, t_command * cmd)
{
    ft_putstr_fd("command not found: ",2);
    ft_putstr_fd(cmd->args[0],2);
    ft_putstr_fd("\n",2);
    free_env(shell->env);
    gr_t(NULL,1);
    exit(127); 
}

void exit_relat_permission (t_shell *shell,t_command * cmd, int flag_permission)
{
    if (flag_permission == 1)
    {
        ft_putstr_fd(cmd->args[0],2);
        ft_putstr_fd(": permission denied\n",2);
        free_env(shell->env);
        gr_t(NULL,1);
    }
    else
    {
        ft_putstr_fd(cmd->args[0],2);
        ft_putstr_fd(": command not found\n",2);
        free_env(shell->env);
        gr_t(NULL,1);
    }
    exit (127);
}

void exec_f_x_ok (t_command *cmd , char * axe)
{
    if (access(axe,X_OK) == 0)
    execve(axe,&cmd->args[0],cmd->conv_env);
}

void relative_path (t_shell *shell, t_command  *cmd)
{
    t_relat s;

    s.env_p = ft_getenv(shell->env,"PATH");
    if (!s.env_p)
        env_p_null(shell,cmd);
    s.path = ft_split(s.env_p,':');
    s.i = 0;
    s.flag_permission = 0;
    s.relat = ft_strjoin("/",cmd->args[0]);
    while (s.path[s.i])
    {
        s.axe = ft_strjoin(s.path[s.i],s.relat);
        if (access(s.axe,F_OK) == 0 )
        {
            exec_f_x_ok(cmd,s.axe);
            s.flag_permission = 1;
            s.i++;
            continue;
        }
        else
            s.i++;
    }
    exit_relat_permission(shell,cmd,s.flag_permission);
}

int check_directory(t_command * cmd)
{
    struct stat buff ;
    if (stat(cmd->args[0],&buff) == 0)
    {
        if(S_ISDIR(buff.st_mode))
        {   
            ft_putstr_fd(cmd->args[0],2);
            ft_putstr_fd(" : is a directory\n",2);
            return (1);
        }
    }
    return (errno);
}

void non_built_in(t_shell *shell , t_command *cmd)
{
    int ret;

    ret = check_directory(cmd); 
    if (ret != 0 && ret != 2)
    {   
        if (ret != 1)
            perror("minishell");
        exit(126);
    }
    absolut_path(shell,cmd);
    relative_path (shell,cmd);
}
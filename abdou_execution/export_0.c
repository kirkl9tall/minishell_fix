#include "parsing_ali/minishell.h"

void none_equal_case_export(t_shell * shell , t_command * cmd,int i,t_env * trav)
{
    if (is_it_alpha_valid(shell,cmd,i)) 
        return;  
    if (is_env_valid(cmd->args[i]) == 0 )
    {
        shell->exit_statut = 1 << 8;
        return;
    }
    if (!is_exist(trav, cmd->args[i]))
        add_exp(&trav,cmd->args[i]);
}

void export_case_equal(t_shell * shell , t_command * cmd,int i,t_env * trav)
{

    char **name;
    name = NULL;
    name = ft_split(cmd->args[i],'=');
    if (is_it_alpha_valid(shell,cmd,i)) 
    {
        i++;
        return;  
    }
    if (is_env_valid(name[0]) == 0 )
    {
        shell->exit_statut = 1 << 8;
        i++;
        return;
    }
    if (!env_similar(trav,name[0],cmd->args[i]))
        add_exp(&trav,cmd->args[i]);

}

void exporting(t_shell *shell,t_command *cmd)
{
    t_env *trav;
    int i;
    i = 1;
    trav = shell->env;

    if (size_counter(cmd->args) == 1)
        print_export_declar(shell->env,cmd->fd_out);
    else
    {
        while (cmd->args[i])
        {
            if (!contain_equal(cmd->args[i]))
                none_equal_case_export(shell,cmd,i,trav);
            else
                export_case_equal(shell,cmd,i,trav);

            i++;
        }
    }
}

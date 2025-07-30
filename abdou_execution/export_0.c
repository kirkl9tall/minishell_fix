#include "parsing_ali/minishell.h"

void exporting (t_shell *shell,t_command *cmd)
{
    char **name;
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
            {
                if (is_it_alpha_valid(shell,cmd,i)) 
                {
                    i++;
                    continue;  
                }
                if (is_env_valid(cmd->args[i]) == 0 )
                {
                    shell->exit_statut = 1 << 8;
                    i++;
                    continue;
                }
                if (!is_exist(trav, cmd->args[i]))
                    add_exp(&trav,cmd->args[i]);
                i++;
                continue;
            }
            else
            {
                name = NULL;
                name = ft_split(cmd->args[i],'=');
                if (is_it_alpha_valid(shell,cmd,i)) 
                {
                    i++;
                    continue;  
                }
                if (is_env_valid(name[0]) == 0 )
                {
                    shell->exit_statut = 1 << 8;
                    i++;
                    continue;
                }
                if (!env_similar(trav,name[0],cmd->args[i]))
                    add_exp(&trav,cmd->args[i]);
            }
            i++;
        }
    }
}
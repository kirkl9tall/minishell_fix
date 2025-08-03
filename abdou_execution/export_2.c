#include "parsing_ali/minishell.h"


int env_similar(t_env *trav1,char * name,char * replace)
{
        while (trav1)
        {
            if (ft_find_env(trav1,name))
            {
                free(trav1->env);
                trav1->env = ft_envdup(replace);
                return 1 ; 
            }
            trav1 = trav1->next;
        }
        return 0;
}
int is_env_valid(char * args)
{
    int i = 0;
    while (args[i])
    {
        if (!((ft_isdigit(args[i]) && i != 0) || (ft_isalpha(args[i])) || args[i] == '_'))
        {
            ft_putstr_fd(" not  a valid identifier\n", 2);
            return 0;
        }    
        i++;
    }
    return (1);
}

int  is_it_alpha_valid(t_shell *shell,t_command *cmd, int i)
{
    if (!(ft_isalpha(cmd->args[i][0])) && cmd->args[i][0] != '_')
    {
        ft_putstr_fd(cmd->args[i],2);
        ft_putstr_fd(" : not a valid identifier\n",2);
        shell->exit_statut = 1 << 8;
        return 1;
    }
    return 0;
}

int contain_equal(char * args)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (args[i])
    {
        if (args[i] == '=')
            {
                flag = 1;
                break;
            }
        i++;
    }
    return (flag);
}

int is_exist(t_env *env, const char *envi)
{
    int        len;

    if (!envi || !env)
        return (0);
    while (env)
    {
        len = ft_strlen(envi);
        if (ft_strncmp(env->env, envi, len) == 0 && ((env->env[len] == '=') || !env->env[len]))
            return (1);
        env = env->next;
    }
    return (0);
}

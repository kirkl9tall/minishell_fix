#include "parsing_ali/minishell.h"

char	*ft_envjoin(char *s1, char *s2)
{
	char	*p;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	if (ft_strlen(s1))
	{
		while (*s1)
			p[i++] = *s1++;
	}
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}
char **conv_envs(t_env *env)
{
    char **envs;
    t_env *scaner;
    int i;
    int len;
    
    scaner = env;
    i = scan_len_env(env);
    envs = malloc(sizeof(char *)*i + 8);
    gr_t(envs , 0);
    i = 0;
    while (scaner)
    {
        len = ft_strlen(env->env);
        envs[i] = malloc(len + 1);
        gr_t(envs[i] , 0);
        ft_bzero(envs[i],len +1);
        envs[i] = ft_strjoin(envs[i],scaner->env);
        i++;
        scaner = scaner->next;
    }
    envs[i] = NULL;
    return envs;
}

void maj_pwd(t_shell *shell)
{
    t_env  *search;
    char * pwd;

    search = shell->env;
    while (search)
    {
     if (ft_find_env(search,"PWD"))
     {
         pwd = getcwd(NULL,0);
        gr_t(pwd , 1);
        // search->env = NULL;
         free(search->env);
         search->env = ft_envjoin("PWD=", pwd);
     }
     search = search->next;
    }
}
int  maj_env (t_shell *shell, char *old_pwd)
{
   t_env  *search;

   search = shell->env;
   while (search)
   {
    if (ft_find_env(search,"OLDPWD"))
    {
        free(search->env);
        if (!old_pwd)
        {
            search->env = ft_envdup("OLDPWD");
            return (0);
        }
        search->env = ft_envjoin("OLDPWD=", old_pwd);
        break;
    }
    search = search->next;
   }
   maj_pwd(shell);
   return (0);
}

void    e_en_vi_ha (t_shell *shell,t_command *cmd)
{
    t_env *env;
    env  = shell->env;
    while (env)
    {
        if (ft_strchr(env->env, '='))
        {
            ft_putstr_fd(env->env,cmd->fd_out);
            write(cmd->fd_out,"\n",1);
        }
        env = env->next;
    }
}

int size_counter (char ** args)
{
    int i = 0;
    while (args[i])
        i++;
    return i;
}
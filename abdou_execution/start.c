#include "parsing_ali/minishell.h"

char    *ft_find_env(t_env *env, const char *envi);
int pipe_nbr(t_command *cmd)
{
    int i  = 0;
    while (cmd)
    {
        cmd = cmd->next;
        i++;
    }
    return (i - 1);
}
int  dupper(t_command *cmd)
{
    if (cmd->fd_out == -1)
        return(0);/// exit status
    else
    {
        cmd->fd_origin = dup(1);
        dup2(cmd->fd_out,1);
    }
    return 1;
}

void free_all(t_shell *shell)
{
    (void)shell;
    // printf("this is the fucntion to free %s\n", shell->line);
}
// void signal_handler_here_doc(int sig)
// {
//     (void)sig;
//     write(1, "\n", 1);
//     free_all(var_ali());
//     exit(130);
// }

// void open_heredz(t_shell *shell, t_command * analyser)
// {
//     if (analyser->fd_here != -1)
//         close (analyser->fd_here);
//     if (analyser->fd1_here != -1)
//         close (analyser->fd1_here);
//     analyser->fd_here = open(shell->rend.rnd_3,O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     analyser->fd1_here = open(shell->rend.rnd_3, O_RDONLY);
//     if (  analyser->fd_here == -1 ||   analyser->fd1_here== -1 )
//         perror("");
//     unlink(shell->rend.rnd_3);
// }

// void child_fill_herd(t_command * analyser,t_redirect * tmp)
// {
//     close(analyser->fd1_here);
//     signal(SIGINT, signal_handler_here_doc);
//     char *line;
//     while (1)
//     {
//         signal(SIGQUIT, SIG_DFL);
//         line = readline("herdoc > ");
//         if (!line)
//             break;
//         if (ft_strcmp(line, tmp->delimiter) == 0)
//             break;
//         write(analyser->fd_here, line, ft_strlen(line));
//         write(analyser->fd_here, "\n", 1);
//         free(line);
//     }
//     close (analyser->fd_here);
//     // close (analyser->fd1_here);
//     close(analyser->fd_origin);
//     close(analyser->fd_origin_in);
//     exit(0);
// }

// int trav_reds(t_shell * shell,t_command * analyser ,t_redirect * tmp)
// {
//     while  (tmp)
//     {
//         if (tmp->type == 3)
//         {
//             open_heredz(shell,analyser);
//             int pid = fork();
//             if (pid == 0)
//             {
//                 child_fill_herd(analyser,tmp);
//             }
//              if (analyser->fd_here > 0)
//                 close(analyser->fd_here);
//             waitpid(pid, &shell->exit_statut, 0);
//             if (WEXITSTATUS(shell->exit_statut) == 130)
//             {
//                return (1) ; 
//             }
//         }
//         tmp = tmp->next;
//     }  
//     return 0; 
// }

// int check_heredoc (t_shell * shell)
// {
//     t_command *analyser;
//     t_redirect *tmp;
//     analyser = shell->cmd;
//     analyser->fd1_here = -1;
//     analyser->fd_here = -1;
//     while (analyser)
//     {
//         tmp = analyser->redirects;
//         if (trav_reds(shell,analyser,tmp))
//             return 1;
//         analyser = analyser->next;
//     }
//     return 0;
// }

// int red_(t_shell * shell ,t_command *cmd, t_redirect * analyser)
// int red_two(t_shell * shell ,t_command *cmd, t_redirect * analyser)
// {
//     cmd->fd_in = open(analyser->filename,O_RDONLY);
//     if  (cmd->fd_in == -1)
//     {
//         ft_putstr_fd(analyser->filename,2);
//         ft_putstr_fd(" : No such file or directory\n",2);
//         shell->exit_statut = 1 << 8;
//         return (1);
//     }
//     return (0);
// }

// int red_one(t_shell * shell ,t_command *cmd, t_redirect * analyser)
// {
//     cmd->fd_out = open(analyser->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
//     if (cmd->fd_out == -1)
//     {
//         ft_putstr_fd(" Permission denied\n",2);
//         shell->exit_statut = 1 << 8;
//         return (1);
//     }
//     return (0);  
// }

// int red_zero(t_shell * shell ,t_command *cmd, t_redirect * analyser)
// {
//     cmd->fd_out = open(analyser->filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
//     if (cmd->fd_out == -1)
//     {
//         ft_putstr_fd(" Permission denied\n",2);
//         shell->exit_statut = 1 << 8;
//         return (1);
//     }
//     return (0);
// }

// int redirection_mode (t_shell * shell ,t_command *cmd, t_redirect * analyser)
// {
//     if (analyser->flag == 1)
//     {
//         ft_putstr_fd("minishell: ambiguous redirect\n",2);
//         shell->exit_statut = 1 << 8;
//         return(1);
//     }
//     else if (analyser->type == 0)
//     {
//         if (red_zero(shell,cmd,analyser) == 1)
//             return (1);
//     }
//     else if (analyser->type == 1)
//     {
//         if (red_one(shell,cmd,analyser) == 1)
//             return (1);           
//     }
//     else if (analyser->type == 2)
//     {
//         if (red_two(shell,cmd,analyser) == 1)
//             return (1);
//     }
//     else if (analyser->type == 3) 
//     {
//         cmd->fd_in =  dup(cmd->fd1_here);  
//         close (cmd->fd1_here);
//     }
//     return (0);
// }

// int redirecter (t_shell *shell , t_command *cmd)
// {
//     t_redirect *analyser;

//     analyser = cmd->redirects;
//     if (analyser)
//     {            

//         while (analyser)
//         {
//             if (redirection_mode (shell,cmd,analyser) == 1)
//                 return (1);
//             analyser = analyser->next;
//         }
//     }
//     return  0;
// }

// int  scan_len_env (t_env *scaner)
// {
//     int i;
//     i = 0;

//     while(scaner)
//     {
//         i++;
//         scaner = scaner->next;
//     }
//     return i; 
// }

// char **conv_envs(t_env *env)
// {
//     char **envs;
//     t_env *scaner;
//     int i;
//     int len;
    
//     scaner = env;
//     i = scan_len_env(env);
//     envs = malloc(sizeof(char *)*i + 8);
//     i = 0;
//     while (scaner)
//     {
//         len = ft_strlen(env->env);
//         envs[i] = malloc(len + 1);
//         ft_bzero(envs[i],len +1);
//         envs[i] = ft_strjoin(envs[i],scaner->env);
//         i++;
//         scaner = scaner->next;
//     }
//     envs[i] = NULL;
//     return envs;
// }

// void maj_pwd(t_shell *shell)
// {
//     t_env  *search;
//     char * pwd;

//     search = shell->env;
//     while (search)
//     {
//      if (ft_find_env(search,"PWD"))
//      {
//          pwd = getcwd(NULL,0);
//          free(search->env);
//          search->env = ft_strjoin("PWD=", pwd);
//      }
//      search = search->next;
//     }
// }
// int  maj_env (t_shell *shell, char *old_pwd)
// {
//    t_env  *search;

//    search = shell->env;
//    while (search)
//    {
//     if (ft_find_env(search,"OLDPWD"))
//     {
//         free(search->env);
//         if (!old_pwd)
//         {
//             search->env = ft_strdup("OLDPWD");
//             return (0);
//         }
//         search->env = ft_strjoin("OLDPWD=", old_pwd);
//     }
//     search = search->next;
//    }
//    maj_pwd(shell);
//    return (0);
// }

// void    e_en_vi_ha (t_shell *shell,t_command *cmd)
// {
//     t_env *env;
//     env  = shell->env;
//     while (env)
//     {
//         if (ft_strchr(env->env, '='))
//         {
//             ft_putstr_fd(env->env,cmd->fd_out);
//             write(cmd->fd_out,"\n",1);
//         }
//         env = env->next;
//     }
// }

// int size_counter (char ** args)
// {
//     int i = 0;
//     while (args[i])
//         i++;
//     return i;
// }

// void cd_home(t_shell * shell, char *old_pwd)
// {
//     char *home;

//     home = ft_getenv(shell->env,"HOME");
//         if (home)
//         {
//             chdir(home);   
//             maj_env(shell,old_pwd);
//             return;  
//         }
//         else
//         {
//             ft_putstr_fd("cd: HOME Not set\n",2);
//             shell->exit_statut = 1 << 8;
//             return;
//         }

// }

// void chdiriha(t_shell * shell,t_command *cmd)
// {
//     char *old_pwd;

//     old_pwd = ft_getenv(shell->env,"PWD");
//     if (size_counter(cmd->args) > 2)
//     {
//         ft_putstr_fd("cd: too many arguments\n",2);
//         shell->exit_statut = 1 << 8 ;
//         return;
//     }
//     else if(size_counter(cmd->args) == 1)
//         cd_home(shell,old_pwd);
//     else 
//     {
//         if (chdir(shell->cmd->args[1]) == -1)
//         {
//             ft_putstr_fd("cd: ",2);
//             ft_putstr_fd(shell->cmd->args[1],2);
//             ft_putstr_fd(": No such file or directory\n",2);
//             shell->exit_statut = 1 << 8 ;
//             return;
//         }
//         maj_env(shell,old_pwd);
//     }
//     return;
// }

// void echo_no_flag (t_command *cmd, int j, int fd)
// {
//     while (cmd->args[j])
//     {
//         ft_putstr_fd(cmd->args[j],fd);
//         if(cmd->args[j+1])
//             write (fd," ",1);
//         j++;
//     }
//     write(fd,"\n",1);
// }

// void  echo_flag(t_command *cmd, int i, int fd)
// {
//     while (cmd->args[i])
//     {
//         if(cmd->args[i+1])
//         {
//             ft_putstr_fd(cmd->args[i],fd);
//             write (fd," ",1);
//         }
//         else
//             ft_putstr_fd(cmd->args[i],fd);
//         i++;
//     }
// }

// int flag_mini (char *args)
// {
//     int  i;
//     i = 1;
//     int breaker;
//     breaker = 0;

//     while(args[i])
//     {
//         if (args[i] != 'n')
//         {
//             breaker = 1;
//             break;
//         }
//         i++;
//     }
//     return breaker;
// }

// void  printer_echo (t_command * cmd,int flag_exist, int j)
// {
//     if (!cmd->args[j])
//         return;
//     if (flag_exist == 1)
//         echo_flag(cmd,j,cmd->fd_out);
//     else
//         echo_no_flag(cmd,j,cmd->fd_out);
// }


// t_echo_f   flag_echo_mac (char *args,t_echo_f f)
// {
//     if (args[0] == '-' && args[1]== 'n')
//     {
//         f.breaker = flag_mini(args);
//         if (f.breaker== 1)
//             return f;
//         f.flag_exist = 1;
//     }
//     else
//         f.breaker = 1;
//     return f;
// }

// void echowiha(t_shell *shell,t_command * cmd)
// {
//     int  j;
//     t_echo_f f;

//     j = 1;
//     f.breaker = 0;
//     f.flag_exist = 0;
//     if (size_counter(cmd->args) == 1)
//     {
//         write(cmd->fd_out,"\n",1);
//         return;
//     }
//     while(cmd->args[j])
//     {
//         f = flag_echo_mac (cmd->args[j],f);
//         if (f.breaker == 1)
//             break;
//         j++;
//     }
//     printer_echo(cmd,f.flag_exist,j);
//     shell->exit_statut = 0;
// }

// int ft_my_env(t_shell *shell, char *var)
// {

//     while (shell->env)
//     {   
//         if(ft_getenv(shell->env,var))
//             return 1;
//         shell->env = shell->env->next;
//     }
//     return 0;
// }

// void p_doublviha(t_shell *shell,t_command * cmd)
// {
//     char *buff;
//     char *result;
//     (void)shell;
//     buff = getcwd(NULL,0);
//     if (!buff)
//         return ; // p erroooorrr daruri=========== ///
//     result = ft_strjoin(buff,"\n");
//     ft_putstr_fd(result, cmd->fd_out);
//     dup2(cmd->fd_origin,1); 
//     dup2(cmd->fd_origin,0); 
// }

// t_env *new_node(char *content)
// {
//     t_env *node;
//     node = malloc(sizeof(t_env));
//     int i = ft_strlen(content);
//     node->env = malloc(i + 1);
//     ft_bzero(node->env ,i + 1);
//     node->env = ft_strjoin(node->env,content);
//     node->next = NULL;
//     return  (node);
// }

// void add_exp (t_env **env,char * content)
// {
//     t_env *last;
//     t_env *node;
//     last = *env;
//     last = last->next;
//     while(last->next)
//         last  = last->next;
//     node  = new_node(content);
//     last->next = node;
// }

// char   **sort_declar_env(t_env * env)
// {
//     char ** str;
//     int i;
//     int j;
//     char *t;
//     i = 0;
//     str = conv_envs(env);
//     while (str[i])
//     {
//         j = i +1;
//         while (str[j])
//         {
//             if (ft_strcmp (str[i],str[j]) > 0)
//             {
//                 t = str[j];
//                 str[j] = str[i];
//                 str[i] = t;
//             }
//             j++;
//         }
//         i++;
//     }
//     return (str);
// }
// void print_export_declar(t_env * trav ,int fd_out)
// {
//     char **sorted;
//     int i;

//     i = 0;
//     sorted = sort_declar_env(trav);
//     while(sorted[i])
//     {
//         ft_putstr_fd("declare -x ",fd_out);
//         ft_putstr_fd(sorted[i],fd_out);
//         ft_putstr_fd("\n",fd_out);
//         i++;
//     }
// }

// void error_export_valid_args(t_command * cmd)
// {
//     ft_putstr_fd("export: `",cmd->fd_out);
//     ft_putstr_fd(cmd->args[2],cmd->fd_out);
//     ft_putstr_fd("': not a valid identifier",cmd->fd_out);
//     write(cmd->fd_out,"\n",1);

// }



// int env_similar(t_env *trav1,char * name,char * replace)
// {
//         while (trav1)
//         {
//             if (ft_find_env(trav1,name))
//             {
//                 ft_bzero(trav1->env,ft_strlen(trav1->env));
//                 trav1->env = ft_strjoin(trav1->env,replace);
//                 return 1 ; 
//             }
//             trav1 = trav1->next;
//         }
//         return 0;
// }
// int is_env_valid (char * args)
// {
//     int i = 0;
//     while (args[i])
//     {
//         if (!((ft_isdigit(args[i]) && i != 0) || (ft_isalpha(args[i])) || args[i] == '_'))
//         {
//             ft_putstr_fd(" not  a valid identifier\n", 2);
//             return 0;
//         }    
//         i++;
//     }
//     return (1);
// }

// int  is_it_alpha_valid (t_shell *shell,t_command *cmd, int i)
// {
//     if (!(ft_isalpha(cmd->args[i][0])) && cmd->args[i][0] != '_')
//     {
//         ft_putstr_fd(cmd->args[i],2);
//         ft_putstr_fd(" : not a valid identifier\n",2);
//         shell->exit_statut = 1 << 8;
//         return 1;
//     }
//     return 0;
// }

// int contain_equal(char * args)
// {
//     int i;
//     int flag;

//     i = 0;
//     flag = 0;
//     while (args[i])
//     {
//         if (args[i] == '=')
//             {
//                 flag = 1;
//                 break;
//             }
//         i++;
//     }
//     return (flag);
// }

// int     is_exist(t_env *env, const char *envi)
// {
//     int        len;

//     if (!envi || !env)
//         return (0);
//     while (env)
//     {
//         len = ft_strlen(envi);
//         if (ft_strncmp(env->env, envi, len) == 0 && ((env->env[len] == '=') || !env->env[len]))
//             return (1);
//         env = env->next;
//     }
//     return (0);
// }

// void exporting (t_shell *shell,t_command *cmd)
// {
//     char **name;
//     t_env *trav;
//     int i;
//     i = 1;
//     trav = shell->env;

//     if (size_counter(cmd->args) == 1)
//         print_export_declar(shell->env,cmd->fd_out);
//     else
//     {
//         while (cmd->args[i])
//         {
//             if (!contain_equal(cmd->args[i]))
//             {
//                 if (is_it_alpha_valid(shell,cmd,i)) 
//                 {
//                     i++;
//                     continue;  
//                 }
//                 if (is_env_valid(cmd->args[i]) == 0 )
//                 {
//                     shell->exit_statut = 1 << 8;
//                     i++;
//                     continue;
//                 }
//                 if (!is_exist(trav, cmd->args[i]))
//                     add_exp(&trav,cmd->args[i]);
//                 i++;
//                 continue;
//             }
//             else
//             {
//                 name = NULL;
//                 name = ft_split(cmd->args[i],'=');
//                 if (is_it_alpha_valid(shell,cmd,i)) 
//                 {
//                     i++;
//                     continue;  
//                 }
//                 if (is_env_valid(name[0]) == 0 )
//                 {
//                     shell->exit_statut = 1 << 8;
//                     i++;
//                     continue;
//                 }
//                 if (!env_similar(trav,name[0],cmd->args[i]))
//                     add_exp(&trav,cmd->args[i]);
//             }
//             i++;
//         }
//     }
// }

// void del_env(t_shell **cmd)
// {
//     t_shell *plo;
//     t_env  *trash;
//     plo = *cmd;
//     trash = plo->env->next;
//     plo->env->next = plo->env->next->next;
//     free(trash);
// }

// char    *ft_find_env(t_env *env, const char *envi)
// {
//     int        len;

//     if (!envi || !env)
//         return (NULL);
//     len = ft_strlen(envi) + 1;
  
//     if (ft_strncmp(env->env, envi, ft_strlen(envi)) == 0 && ((env->env[ft_strlen(envi)] == '=') || !env->env[ft_strlen(envi)]))
//         return (env->env + len);
//     return (NULL);
// }

// int first_elem_unset(t_shell *shell, t_command *cmd)
// {
//     t_env *env;
//     t_env  *trash;
//     env = shell->env;
//     if(ft_find_env(env,cmd->args[1]))
//     {
//         trash = env;
//         shell->env = env->next;
//         free(trash);
//         return 1 ;
//     }
//     return 0;
// }

// void unsetiha (t_shell *shell,t_command *cmd)
// {
//     t_env *env;
//     t_env  *trash;
//     int i;
    
//     i = 1;
//     while (cmd->args[i])
//     {
//         if (first_elem_unset(shell,cmd))
//             continue;
//         env = shell->env;
//         while (env)
//         {
//             if(ft_find_env(env->next,cmd->args[i]))
//             {
//                 trash = env->next;
//                 env->next = trash->next;
//                 free (trash);
//                 break;    
//             }
//             env = env->next;
//         }
//         i++;
//     }
// }


// t_ex_f	ft_atoi_exit(const char *str)
// {
// 	int	i;
// 	int	sn;
// 	long	rest;
// 	t_ex_f res;
// 	sn = 1;
// 	rest = 0;
// 	i = 0;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
// 		i++;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			sn = -1;
// 		i++;
// 	}
// 	while (str[i] && str[i] >= '0' && str[i] <= '9')
// 	{
// 		rest = rest * 10 + (str[i] - '0');
// 		if (rest > INT_MAX   || rest < INT_MIN)
// 			res.flag = 1;
//         i++;
// 	}
// 	res.res = rest *sn;
// 	return (res);
// }

// void exit_numeric_required (t_command *cmd,t_shell *shell)
// {
//     ft_putstr_fd("exit\n",2);
//     ft_putstr_fd(cmd->args[0],2);
//     ft_putstr_fd(" : ",2);
//     ft_putstr_fd(cmd->args[1],2);
//     ft_putstr_fd(" : numeric argument required\n",2);
//     close(shell->cmd->fd_origin);
//     close(shell->cmd->fd_origin_in);
//     exit(2);
// }
// void exit_number(t_shell *shell,t_command *cmd)
// {
//     t_ex_f s;

//     s = ft_atoi_exit(cmd->args[1]);
//     shell->exit_statut = s.res;
//     if (s.flag == 1)
//     {
//         ft_putstr_fd("too many arguments\n",2);
//         close(shell->cmd->fd_origin);
//         close(shell->cmd->fd_origin_in);
//         exit (2);
//     }
//     write (2,"exit\n",5);
//     close(shell->cmd->fd_origin);
//     close(shell->cmd->fd_origin_in);
//     exit(shell->exit_statut);
// }
// void exit_arg_three(t_shell *shell , t_command *cmd)
// {  
//     int j;
//     int i;

//     i = 0;
//     while (cmd->args[i])
//     {
//         j = 0;
//         while (cmd->args[i][j])
//         {
//             if (ft_isalpha(cmd->args[1][i]))
//                 exit_numeric_required(cmd,shell);
//             j++;
//         }
//         i++;
//     }
//     ft_putstr_fd("too many arguments\n",2);
//     shell->exit_statut = 1 << 8;
// }

// void exit_function(t_shell *shell , t_command *cmd)
// {
//     int i;

//     i = 0;
//     if (size_counter(cmd->args) == 1)
//     {
//         close(shell->cmd->fd_origin);
//         close(shell->cmd->fd_origin_in);
//         write (2,"exit\n",5);
//         exit(0);
//     }
//     else if (size_counter(cmd->args) == 2)
//     {
//         while (cmd->args[1][i])
//         {
//             if (ft_isalpha(cmd->args[1][i]))
//                 exit_numeric_required(cmd,shell);
//             i++;
//         }
//         exit_number(shell,cmd);
//     }
//     exit_arg_three(shell,cmd);
// }
// void dup_close(t_command *cmd)
// {
//     dup2(cmd->fd_origin,1);
//     dup2(cmd->fd_origin_in,0);
//     close(cmd->fd_origin);
//     close(cmd->fd_origin_in);
// }
// int check_func_buil (t_shell *shell,t_command *cmd)
// {
//     if (shell->cmd->args == NULL)
//         return -1;
//     if (shell->cmd->args[0] == NULL)
//         return -1;
//     if(ft_strcmp(cmd->args[0],"env") == 0 )
//         e_en_vi_ha(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"cd") == 0 )
//         chdiriha(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"echo") == 0 )
//         echowiha(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"pwd") == 0 )
//         p_doublviha(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"export") == 0 )
//         exporting(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"unset") == 0 )
//         unsetiha(shell,cmd);
//     else if(ft_strcmp(cmd->args[0],"exit") == 0 )
//         exit_function(shell,cmd);
//     else
//         return (0);
//     dup_close(cmd);
//     return  (1); 
// }

// void absolut_path(t_command * cmd)
// {
//     if  (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
//     {
//          if (access(cmd->args[0],F_OK) == 0)
//         {
//             if (access(cmd->args[0],X_OK)== 0)
//                 execve(cmd->args[0],&cmd->args[0],cmd->conv_env);
//             else
//             {
//                 ft_putstr_fd("Permission denied\n",2);
//                 exit(126); //exit status 
//             }
//         }
//         else
//         {
//             ft_putstr_fd("No such file or directory\n",2);
//             exit (127); //// exit status 
//         }
//     }
// }

// void env_p_null (t_command * cmd)
// {
//     ft_putstr_fd("command not found: ",2);
//     ft_putstr_fd(cmd->args[0],2);
//     ft_putstr_fd("\n",2);
//     exit(127); 
// }

// void exit_relat_permission (t_command * cmd, int flag_permission)
// {
//     if (flag_permission == 1)
//     {
//         ft_putstr_fd(cmd->args[0],2);
//         ft_putstr_fd(": permission denied\n",2);
//     }
//     else
//     {
//         ft_putstr_fd(cmd->args[0],2);
//         ft_putstr_fd(": command not found\n",2);
//     }
//     exit (127);
// }

// void exec_f_x_ok (t_command *cmd , char * axe)
// {
//     if (access(axe,X_OK) == 0)
//     execve(axe,&cmd->args[0],cmd->conv_env);
// }

// void relative_path (t_shell *shell, t_command  *cmd)
// {
//     t_relat s;

//     s.env_p = ft_getenv(shell->env,"PATH");
//     if (!s.env_p)
//         env_p_null(cmd);
//     s.path = ft_split(s.env_p,':');
//     s.i = 0;
//     s.flag_permission = 0;
//     s.relat = ft_strjoin("/",cmd->args[0]);
//     while (s.path[s.i])
//     {
//         s.axe = ft_strjoin(s.path[s.i],s.relat);
//         if (access(s.axe,F_OK) == 0 )
//         {
//             exec_f_x_ok(cmd,s.axe);
//             s.flag_permission = 1;
//             s.i++;
//             continue;
//         }
//         else
//             s.i++;
//     }
//     exit_relat_permission(cmd,s.flag_permission);
// }

// int check_directory(t_command * cmd)
// {
//     struct stat buff ;
//     if (stat(cmd->args[0],&buff) == 0)
//     {
//         if(S_ISDIR(buff.st_mode))
//         {   
//             ft_putstr_fd(cmd->args[0],2);
//             ft_putstr_fd(" : is a directory\n",2);
//             return (1);
//         }
//     }
//     return (errno);
// }

// void non_built_in(t_shell *shell , t_command *cmd)
// {
//     int ret;

//     ret = check_directory(cmd); 
//     if (ret != 0 && ret != 2)
//     {   
//         if (ret != 1)
//             perror("minishell");
//         exit(126);
//     }
//     absolut_path(cmd);
//     relative_path (shell,cmd);
// }
// void analyse_check_dups(t_command * cmd)
// {
//  if (cmd->fd_out > 1)
//     {
//         dup2(cmd->fd_out,1);
//         close (cmd->fd_out);
//         cmd->fd_out = 1;
//     }
//     if (cmd->fd_in > 0)
//     {
//         dup2(cmd->fd_in,0);
//         close (cmd->fd_in);
//         cmd->fd_in = 0;
//     }
// }
// void analyser_command (t_shell *shell,t_command *cmd)
// {
//     signal(SIGINT, shell->defau_sigc);
//     signal(SIGQUIT, shell->defau_sigq);
//     cmd->fd_out = 1;
//     cmd->fd_in = 0;
//     if (redirecter(shell,cmd) == 1)
//         exit(1);
//          if (!cmd->args)
//         exit(0);
//     if (!cmd->args[0][0])
//     {
//         write(2, "Command not found\n", 18);
//         exit(0);
//     }
//     analyse_check_dups(cmd);
//     if (check_func_buil(shell,cmd) == 1)
//         exit(shell->exit_statut >> 8);
//     cmd->conv_env = conv_envs(shell->env);
//     non_built_in(shell,cmd);
// }


void signal_handler_child()
{
    
    exit(1);// must make exit status of ctrl +c 
}
void signal_handler_parent()
{
    // write(1,"\n",2);
}
// int check_cmd(t_command *cmd)
// {
//     t_command * trav;
//     int i = 0;
//     trav = cmd;
//     while (trav)
//     {
//         if (trav->args)
//             i++;
//         trav = trav->next;
//     }
//     if (cmd->redirects)
//     {
//         while (cmd->redirects)
//         {
//             if (cmd->redirects->type != 3)
//                 i++;
//             cmd->redirects = cmd->redirects->next;
//         }
//     }
//     return i ;
// }
// void dup_child_pipe(t_shell * shell)
// {

// }
void child_pipe(t_shell * shell,t_command * cmd,t_hp s)
{
                cmd->fd_out = 1;
            cmd->fd_in = 0;
            if(shell->cmd->fd_origin > 2)
                close(shell->cmd->fd_origin);
            if(shell->cmd->fd_origin_in > 2)
                close(shell->cmd->fd_origin_in);
            cmd->fd_origin = 1;
            cmd->fd_origin_in = 0;
            if (s.i > 0)
            {
                dup2(s.p, 0);
                close(s.p);
            }
            if (s.i < s.nb_cmd - 1)
            {
                dup2(s.pipe_fd[1], 1);
                close(s.pipe_fd[1]);
                close(s.pipe_fd[0]);
            }
            s.pid = NULL;
            analyser_command(shell,cmd);
            free_env(shell->env);
            gr_t(NULL,1);
            close_fds();
            exit(0);
}
void wait_childs(t_shell *shell, t_hp s)
{
    s.i = 0;
    while (s.i < s.nb_cmd)
    {
        waitpid(s.pid[s.i],&shell->exit_statut,0);
        s.i++;
    }
    if (s.p != -1)
            close(s.p);       
    s.pid = NULL;
}
void handle_pipes(t_shell *shell)
{
    t_hp s;
    t_command *cmd;

    cmd = shell->cmd;
    s.nb_cmd = pipe_nbr(cmd) + 1;
    s.pid = malloc(s.nb_cmd * sizeof(int));
    gr_t(s.pid , 0);
    s.i = 0;
    s.p = -1;
    while (s.i < s.nb_cmd && cmd)
    {
        if (s.i < s.nb_cmd - 1)
            pipe(s.pipe_fd);
        s.pid[s.i]= fork();
        if (!s.pid[s.i])
            child_pipe(shell,cmd,s);
        if (s.p != -1)
            close(s.p);
        if (s.i < s.nb_cmd - 1)
        {
            close(s.pipe_fd[1]);
            s.p = s.pipe_fd[0];
        }
        s.i++;
        cmd = cmd->next;
    }
    wait_childs(shell,s);
}

void close_fds()
{
    int i;
    i = 3;
    while (i <1024)
    {
        close(i); 
        i++;
    }
}
int start(t_shell *shell)
{
    // t_command *analyzer;
    int nbr_pipe;
    // analyzer = shell->cmd;
    init_fds(shell);
    signal(SIGINT,SIG_IGN);
    // if (check_heredoc(shell))
    //     return (0);
    // int f = check_cmd(shell->cmd);
    // if (!f)
    // {
    //     while (shell->cmd)
    //     {
    //         if(shell->cmd->fd_here != -1)
    //             close (shell->cmd->fd1_here);
    //         if(shell->cmd->fd1_here != -1)
    //             close (shell->cmd->fd1_here);
    //         shell->cmd = shell->cmd->next;
    //     }
    //     return 0;
    // }
    nbr_pipe = pipe_nbr(shell->cmd);
    if (nbr_pipe == 0)
    {
        if (redirecter(shell , shell->cmd) == 1)
        {
            close_fds();
            return 0;
        }
        dup2(shell->cmd->fd_out,1);
        dup2(shell->cmd->fd_in,0);
        if (check_func_buil(shell,shell->cmd) == 1)
            return 0;
    }
    handle_pipes(shell);
    dup2(shell->cmd->fd_origin,1);
    dup2(shell->cmd->fd_origin_in,0);
    close(shell->cmd->fd_origin);
    close(shell->cmd->fd_origin_in);
    return 0;
}

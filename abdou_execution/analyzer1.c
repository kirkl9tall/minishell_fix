// #include "parsing_ali/minishell.h"


// int check_func_buil (t_shell *shell,int fd);

// int pipe_nbr(t_command *cmd)
// {
//     int i  = 0;
//     while (cmd)
//     {
//         cmd = cmd->next;
//         i++;
//     }
//     return (i -1);
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

// int  ft_finder (char *big,char * little )
// {
//     size_t	i;
//     size_t	j;

//     i = 0;
//     if (little[0] == '\0')
//         return (0);
//     while (big[i])
//     {
//         j = 0;
//         while (big[i + j] && little[j] && big[i + j] == little[j])
//             j++;
//         if (little[j] == '\0')
//             return (1);
//         i++;
//     }
//     return (0);
// }

// char **conv_envs(t_shell *cmd)
// {
//     char **envs;
//     t_env *scaner;
//     scaner = cmd->env;
//     int i;
//     int len;
//     i = scan_len_env(cmd->env);
//     envs = malloc(sizeof(char *)*i + 8);
//     i = 0;
//     while (scaner)
//     {
//         len = ft_strlen(cmd->env->env);
//         envs[i] = malloc(len + 1);
//         ft_bzero(envs[i],len +1);
//         envs[i] = ft_strjoin(envs[i],scaner->env);
//         i++;
//         scaner = scaner->next;
//     }
//     envs[i] = NULL;
//     return envs;
// }

// // int redirecter_parent (t_command *cmd)
// // {
// //     t_redirect *analyser;
// //     analyser = cmd->redirects;
// //     int fd_file = 1;
// //     if (analyser)
// //     {
// //         while (analyser)
// //         {
// //             if (analyser->flag == 1)
// //             {
// //                 printf ("minishell: ambiguous redirect partent\n");
// //                 return (-1);
// //             }
// //             if (analyser->type == 0)
// //             {
// //                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
// //                     if (fd_file == -1)
// //                     {
// //                         printf("failed creation ! \n");
// //                         return fd_file;
// //                     }
// //                 dup(fd_file);
// //                 // close (fd_file);
// //             }
// //             else if (analyser->type == 1)
// //             {
// //                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
// //                     if (fd_file == -1)
// //                     {
// //                         printf("failed creation ! \n");
// //                         return fd_file;
// //                     }
// //                 dup(fd_file);
// //                 // close (fd_file);                 
// //             }
// //             else if (analyser->type == 2)
// //             {
// //                 fd_file = open(analyser->filename,O_RDONLY);
// //                 if  (fd_file == -1)
// //                 {
// //                     printf("%s : No such file or directory !\n",analyser->filename);
// //                     return fd_file;
// //                 }
// //             }
// //             else if (analyser->type == 3)
// //             printf("Heredoc: hahaaadi %s\n", analyser->filename);
// //             else
// //             printf("Unknown redirection type: %d\n", analyser->type);
// //             analyser = analyser->next;
// //         }
// //     }
// //     return  fd_file;
// // }
// int redirecter_no_pipe (t_command *cmd)
// {
//     t_redirect *analyser;
//     analyser = cmd->redirects;
//     int fd_file = 1;
//     if (analyser)
//     {
//         while (analyser)
//         {
//             if (analyser->flag == 1)
//             {
//                 ft_putstr_fd("minishell: ambiguous redirect child\n",2);
//                 return(-1);
//             }
//             if (analyser->type == 0)
//             {
//                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
//                     if (fd_file == -1)
//                     {
//                         ft_putstr_fd("failed creation ! \n",2);
//                         return fd_file;
//                     }
//             }
//             else if (analyser->type == 1)
//             {
//                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
//                     if (fd_file == -1)
//                     {
//                         ft_putstr_fd("failed creation ! \n",2);
//                         return fd_file;
//                     }               
//             }
//             else if (analyser->type == 2)
//             {
//                 fd_file = open(analyser->filename,O_RDONLY);
//                 if  (fd_file == -1)
//                 {
//                     ft_putstr_fd(analyser->filename,2);
//                     ft_putstr_fd(" : No such file or directory !\n",2);
//                     return fd_file;
//                 }
//             }
//             else if (analyser->type == 3) 
//             {
//                 return 1;
//             }
//             else
//             printf("Unknown redirection type: %d\n", analyser->type);
//             analyser = analyser->next;
//         }
//     }
//     return  fd_file;
// }

// int redirecter (t_command *cmd)
// {
//     t_redirect *analyser;
//     analyser = cmd->redirects;
//     int fd_file = 1;
//     if (analyser)
//     {
//         while (analyser)
//         {
//             if (analyser->flag == 1)
//             {
//                 ft_putstr_fd("minishell: ambiguous redirect child\n",2);
//                 return(-1);
//             }
//             if (analyser->type == 0)
//             {
//                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT | O_TRUNC ,0644);
//                     if (fd_file == -1)
//                     {
//                         ft_putstr_fd("failed creation ! \n",2);
//                         return fd_file;
//                     }
//                 dup2(fd_file,1);
//                 close (fd_file);
//             }
//             else if (analyser->type == 1)
//             {
//                 fd_file = open(analyser->filename,O_WRONLY | O_CREAT |O_APPEND,0644);
//                     if (fd_file == -1)
//                     {
//                         ft_putstr_fd("failed creation ! \n",2);
//                         return fd_file;
//                     }
//                 dup2(fd_file,1);
//                 close (fd_file);                 
//             }
//             else if (analyser->type == 2)
//             {
//                 fd_file = open(analyser->filename,O_RDONLY);
//                 if  (fd_file == -1)
//                 {
//                     ft_putstr_fd(analyser->filename,2);
//                     ft_putstr_fd(" : No such file or directory !\n",2);
//                     return fd_file;
//                 }
//             }
//             else
//             printf("Unknown redirection type: %d\n", analyser->type);
//             analyser = analyser->next;
//         }
//     }
//     return  fd_file;
// }

// int ft_my_env(t_shell *cmd, char *var)
// {

//     while (cmd->env)
//     {   
//         if(ft_finder(cmd->env->env,var))
//             return 1;
//         cmd->env = cmd->env->next;
//     }
//     return 0;
// }

// int analyser_command (t_shell *shell)
// {
//     t_command *cmd = shell->cmd;
//     int red;

//     red = redirecter(cmd);
//     if ( red == -1)
//         exit (1);/// exit status 
//     int build = check_func_buil(shell,red);
//     if (build == 1 || build == -1)
//         return;
//     cmd->conv_env = conv_envs(shell);
//     //------------------------------------------ part : check  path if absolut ----------//
//     if (build == 0)
//     {
//         if  (cmd->args[0][0] == '.' ||cmd->args[0][0] == '/')
//         {
//             if (access(cmd->args[0],F_OK) == 0)
//             {
//                 if (access(cmd->args[0],X_OK)== 0)
//                 {
//                     execve(cmd->args[0],&cmd->args[0],cmd->conv_env);
//                     exit(1);/// exit with exit status
//                 }
//                 else
//                 {
//                     ft_putstr_fd("Permission denied  ! \n",2);
//                 }
//             }
//             else
//                 ft_putstr_fd("No such file or  directory !\n",2);
//         }
//         //------------------------------------------ part : check  path if absolut ----------//
//         else
//         {
//             char *env_p;
//             env_p = ft_getenv(shell->env,"PATH");//// wash katunseta mn linkedlist original 
//             if (!env_p)
//             {
//                 ft_putstr_fd("command not found: ",2);
//                 ft_putstr_fd(cmd->args[0],2);
//                 ft_putstr_fd("\n",2);
//                 return 0;
//             }
//             char **path = ft_split(env_p,':');
//             int i = 0;
//             char * relat;
//             char *axe = NULL;
//             relat = ft_strjoin("/",cmd->args[0]);
//             while (path[i])
//             {
//                 axe = ft_strjoin(path[i],relat);
//                 if (access(axe,X_OK) == 0)
//                 {
//                     execve(axe,&cmd->args[0],cmd->conv_env);
//                     return 0;
//                 }
//                 else
//                     i++;
//             }
//             ft_putstr_fd(cmd->args[0],2);
//             ft_putstr_fd(": command not found\n",2);
//         }
//     }
//     else
//     exit (1);
//     return 0;
// }

// void    e_en_vi_ha (t_shell *cmd)
// {
//     int fd;
//     fd = redirecter_parent(cmd->cmd);
//     while (cmd->env)
//     {
//         if (ft_strchr(cmd->env->env, '='))
//         {
//             ft_putstr_fd(cmd->env->env,fd);
//             write(fd,"\n",1);
//         }
//         cmd->env = cmd->env->next;
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

// void unsetiha (t_shell *cmd)
// {
//     while (cmd->env->next)
//     {
//         if(ft_getenv(cmd->env->next->env,cmd->cmd->args[1]))
//         {
//             del_env(&cmd);
//             return;    
//         }
//         cmd->env = cmd->env->next;
//     }
// }
// void p_doublviha(t_shell *cmd)
// {
//     int fd;

//     char buff[1000];
//     if (ft_my_env(cmd,"PWD") == 0 )////////////vto9baaaaaaaaaaaaaaaaaaa
//     {
//         ///// we need pwd  so we need to implememnt each  my env with the var needed 
//         ft_putstr_fd(cmd->cmd->args[0],2);
//         ft_putstr_fd("%s  : No such file or directory\n",2);
//         return;
//     }
//     if (getcwd(buff,1000) == NULL)
//         return ; // p erroooorrr daruri=========== ///
//     printf ("%s\n",buff);

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

// void echowiha(t_shell *cmd, int fd)
// {
//     int i  = 1;

//     if (!cmd->cmd->args[1])
//     {
//         write(fd,"\n",1);
//         return;
//     }
//     int  j = 1;
//     int breaker = 0;
//     int flag_exist = 0;
//     while(cmd->cmd->args[j])
//     {
//         i = 1;
//         if (cmd->cmd->args[j][0] == '-' && cmd->cmd->args[j][1]== 'n')
//         {
//             while(cmd->cmd->args[j][i])
//             {
//                 if (cmd->cmd->args[j][i] != 'n')
//                 {
//                     breaker = 1;
//                     break;
//                 }
//                 i++;
//             }
//             if (breaker ==1)
//                 break;
//             flag_exist = 1;
//         }
//         else
//             break;
//         if (breaker ==1)
//             break;
//         j++;
//     }
//     if (!cmd->cmd->args[j])
//         return;
//     if (flag_exist == 1)
//         echo_flag(cmd->cmd,j,fd);
//     else
//         echo_no_flag(cmd->cmd,j,fd);
//     return;
// }
// // ================================= jereb dyal ali ========= env linked list ///// 
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
// int ft_finder_env(t_env **env,char *name,char * arg)
// {
//     t_env *searcher;

//     searcher = *env;

//     while (searcher)
//     {
//         if (ft_finder(searcher->env,name) == 1)
//             {
//                 ft_bzero(searcher->env,ft_strlen(searcher->env));
//                 searcher->env = ft_strjoin(searcher->env,arg);
//                 return 1;
//             }
//             searcher =searcher->next;
//     }
//     return 0;
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

// void exporting (t_shell *cmd)
// {
//     char **name;
//     char *dec;
//     dec = NULL;
//     int fd;
//     fd = redirecter_parent(cmd->cmd);
//     if (cmd->cmd->args[1] == NULL )
//     {
//         while (cmd->env)
//         {
//             dec = ft_strjoin(dec,"declare -x ");
//             dec = ft_strjoin(dec,cmd->env->env);
//             dec = ft_strjoin(dec,"\n");
//             ft_putstr_fd(dec,fd);
//             cmd->env = cmd->env->next;
//         }
//     }
//     else
//     {
//         if (cmd->cmd->args[2])
//         {
//             ft_putstr_fd("export: `",fd);
//             ft_putstr_fd(cmd->cmd->args[2],fd);
//             ft_putstr_fd("': not a valid identifier",fd);
//             write(fd,"\n",1);
//             return;
//         }
//         name = ft_split(cmd->cmd->args[1],'=');
//         if (ft_getenv(cmd->env,name[0]))
//             return;
//         add_exp(&cmd->env,cmd->cmd->args[1]);
//     }
// }


// int  maj_env (t_shell *shell, char *old_pwd)
// {
//     t_env *searcher;
//     int  i = 0;
//     char **conv = conv_envs(shell);
//     char *conc = NULL;
//     char  new_pwd[1000];
//     char **name;
//     searcher = shell->env;
//     while (searcher->next)
//     {
//         name = ft_split(conv[i],'=');
//         if (ft_strcmp(name[0],"OLDPWD") == 0)
//             {
//                 conc = ft_strjoin(conc,"OLDPWD=");
//                 conc = ft_strjoin(conc, old_pwd);
//                 ft_bzero(searcher->env,ft_strlen(searcher->env));
//                 searcher->env = ft_strjoin(searcher->env,conc);
//                 conc = NULL;
//             }
//         else if (ft_strcmp(name[0],"PWD") == 0)
//             {
//                 conc = ft_strjoin(conc,"PWD=");
//                 conc = ft_strjoin(conc, getcwd(new_pwd,1000));
//                 ft_bzero(searcher->env,ft_strlen(searcher->env));
//                 searcher->env = ft_strjoin(searcher->env,conc);
//                 conc = NULL;
//             }
//             searcher = searcher->next;
//             i++;
//     }
//     return 0;
// }
// int size_counter (char ** args)
// {
//     int i = 0;
//     while (args[i])
//         i++;
//     return i;
// }

// void chdiriha(t_shell * shell)
// {
//     char *old_pwd;
//     old_pwd = ft_getenv(shell->env,"PWD");
//     if (size_counter(shell->cmd->args) > 2)
//     {
//         ft_putstr_fd("cd: too many arguments\n",2);
//     }
//     else if(!shell->cmd->args[1]) //  || shell->cmd->args[1][0] == '~'
//     {
//         char *home = ft_getenv(shell->env,"HOME");
//         if (home)
//         {
//             chdir(home);   
//             maj_env(shell,old_pwd);
//             return;  
//         }
//         else
//         {
//             ft_putstr_fd("cd: HOME Not set\n",2);
//             return;
//         }
//     }
//     else 
//     {
//         if (chdir(shell->cmd->args[1]) == -1)
//         {
//             ft_putstr_fd("cd: ",2);
//             ft_putstr_fd(shell->cmd->args[1],2);
//             ft_putstr_fd(": No such file or directory\n",2);
//             return;//// exit status
//         }
//         maj_env(shell,old_pwd);
//     }
//     return;
// }

// int check_func_buil (t_shell *shell, int fd)
// {
//     if (shell->cmd->args == NULL)
//         //check  var; 
//         // fd = redirecter(shell->cmd);
//         return -1;
//     if (shell->cmd->args[0] == NULL)
//         return -1;
//     if(ft_strcmp(shell->cmd->args[0],"env") == 0 )
//         e_en_vi_ha(shell);
//     else if(ft_strcmp(shell->cmd->args[0],"cd") == 0 )
//         chdiriha(shell);
//     else if(ft_strcmp(shell->cmd->args[0],"echo") == 0 )
//         echowiha(shell,fd);
//     else if(ft_strcmp(shell->cmd->args[0],"pwd") == 0 )
//         p_doublviha(shell);
//     else if(ft_strcmp(shell->cmd->args[0],"export") == 0 )
//         exporting(shell);
//     else if(ft_strcmp(shell->cmd->args[0],"unset") == 0 )
//         unsetiha(shell);
//     else if(ft_strcmp(shell->cmd->args[0],"exit") == 0 )
//         exit(0);
//     else
//         return (0);
//     return  (1); ///// exit status
// }

// t_shell *var_ali(void)
// {
// 	static t_shell shell;
// 	return (&shell);
// }
// // void signal_handler(int sig)
// // {
// // 	(void)sig;
// // 	write (1, "\n", 1);
// // 	free_all(var_ali() );
// // }
// // void free_all(t_shell *shell)
// // {
// // 	int  i = 0;
// // 	// t_env * trav = shell->env; 
// // 	// t_env * tmp_env;
// // 	t_redirect * tmp_red;
// // 	t_command *tmp_cmd;
// // 	// t_token_node * tmp_token;
	
// // 	//======================free  cmd ========================//
// // 	while (shell->cmd)
// // 	{	
// // 		tmp_cmd = shell->cmd->next;
// // 		// args  freee
// // 		while (shell->cmd->args[i])
// // 		{
// // 			free(shell->cmd->args[i]);
// // 			i++;
// // 		}
// // 		free (shell->cmd->args);
// //         // printf("------------------------args freed\n");
// // 		// redirects
// // 		while (shell->cmd->redirects)
// // 		{
// //             tmp_red = shell->cmd->redirects;
// //             if (shell->cmd->redirects->filename)
// //                 free (shell->cmd->redirects->filename);
// //             if (shell->cmd->redirects->delimiter)
// // 			    free (shell->cmd->redirects->delimiter);
// // 			free (shell->cmd->redirects);
// // 			shell->cmd->redirects = tmp_red;
// // 		}
// // 		// conv_env free
// // 		// i = 0;

// // 		// while (shell->cmd->conv_env)
// // 		// {
// //         //     // if (shell->cmd->conv_env[i])
// // 		// 	free(shell->cmd->conv_env[i]);
// // 		// 	i++;
// // 		// }

// // 		// free (shell->cmd->conv_env);
// // 		// env linked list  freee
// // 		shell->cmd = tmp_cmd;
// // 	}
// // 	//=======================free token_list====================//

// // 	//=================================free env====================//
// // 	// while (trav)
// // 	// {
// // 	// 	tmp_env = trav->next;
// // 	// 	free (trav->title);
// // 	// 	free (trav->env);
// // 	// 	free (trav);
// // 	// 	trav = tmp_env;
// // 	// }
// // 	// i = 0;
// // 	// while (shell->ps)
// // 	// {
// // 	// 	shell->ps[i];
// // 	// 	i++;
// // 	// }
// // }

// int start (t_shell *shell)
// {
//     t_shell *exc;
//     int i = 0;
//     exc = malloc(sizeof(t_shell));
//     exc->cmd = shell->cmd;
//     exc->env = shell->env;
//     int nbr_pipe = pipe_nbr(shell->cmd);
//     int chil[nbr_pipe + 1];
//     shell->ps = malloc(sizeof(t_pip)*nbr_pipe);
//     while (i < nbr_pipe)
//         pipe(shell->ps[i++].p);
//     i = 0;
//     if(nbr_pipe == 0)
//     {
//         int red = redirecter_no_pipe(exc->cmd);
//         if (red == -1 )
//             return 0;
//         if (check_func_buil(exc,red) == 1)
//             return 0;
//     }

//     while(exc->cmd)                                                                 
//     {
//         chil[i] = fork();                                                                           
//         if  (chil[i] == 0)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
//         {    
//             if (i > 0)
//                 dup2(shell->ps[i-1].p[0],0);

//             if (i < nbr_pipe)
//                 dup2(shell->ps[i].p[1],1);

//             int j = 0;
//             while (j < nbr_pipe)
//             {
//                 close(shell->ps[j].p[1]);
//                 close(shell->ps[j].p[0]); 
//                 j++;
//             }
//             analyser_command(exc);
//         }
//         i++;
//         exc->cmd = exc->cmd->next;
//     }
//     int j = 0;
//     while (j < nbr_pipe)
//     {
//         close(shell->ps[j].p[1]);
//         close(shell->ps[j].p[0]); 
//         j++;
//     }
//     j = 0 ;
//     while (j < i)
//     {
//         waitpid(chil[j],NULL,0);
//         j++;
//     }
//     return 0;
// }

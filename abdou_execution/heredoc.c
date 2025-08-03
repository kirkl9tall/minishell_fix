#include "parsing_ali/minishell.h"


// void signal_handler_here_doc(int sig)
// {
//     (void)sig;
//     write(1, "\n", 1);
//     // free_all(var_ali());
//     close_fds();
//     exit(130);
// }

// void open_heredz(t_shell *shell, t_command * analyser)
// {
//     if (analyser->fd_here != -1)
//     {
//         close (analyser->fd_here);
//         analyser->fd_here = -1;    
//     }
//     if (analyser->fd1_here != -1)
//     {
//         close (analyser->fd1_here);
//         analyser->fd1_here = -1;    
//     }
//     analyser->fd_here = open(shell->rend.rnd_3,O_CREAT | O_WRONLY | O_TRUNC, 0644);
//     analyser->fd1_here = open(shell->rend.rnd_3, O_RDONLY);
//     if (  analyser->fd_here == -1 ||   analyser->fd1_here== -1 )
//         perror("");
//     unlink(shell->rend.rnd_3);
//     // analyser->fd_in = dup(analyser->fd1_here);
//     // close(analyser->fd1_here);
    
// }
// void child_fill_herd(t_command * analyser,t_redirect * tmp)
// {
//     char *line;

//     signal(SIGINT, signal_handler_here_doc);
//     while (1)
//     {
//         line = readline("herdoc > ");
//         if (!line)
//             break;
//         if (ft_strcmp(line, tmp->delimiter) == 0)
//             break;
//         write(analyser->fd_here, line, ft_strlen(line));
//         write(analyser->fd_here, "\n", 1);
//         // free(line);
//         line = NULL;
//     }
//     close_fds();
//     gr_t(NULL,1);
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
//             close(analyser->fd_here);
//             analyser->fd_in = dup(analyser->fd1_here);
//             close(analyser->fd1_here);
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
void signal_handler_here_doc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    free_all(var_ali());
    exit(130);
}
void child_heredoc_exec(t_command *analyser,t_redirect *tmp)
{
    char *line;

    signal(SIGINT, signal_handler_here_doc);
    while (1)
    {
        signal(SIGQUIT, SIG_DFL);
        line = readline("herdoc > ");
        if (!line)
            break;
        if (ft_strcmp(line, tmp->delimiter) == 0)
            break;
        write(analyser->fd_here, line, ft_strlen(line));
        write(analyser->fd_here, "\n", 1);
        free(line);
    }
    close_fds();
    exit(0);
}
int type_three_heredoc(t_shell *shell , t_command *analyser,t_redirect *tmp)
{
    analyser->fd_here = open(shell->rend.rnd_3,O_CREAT | O_WRONLY | O_TRUNC, 0644);
    analyser->fd1_here = open(shell->rend.rnd_3, O_RDONLY);
    if (analyser->fd_here == -1 || analyser->fd1_here== -1)
        perror("");
    unlink(shell->rend.rnd_3);
    int pid = fork();
    if (!pid)
        child_heredoc_exec(analyser,tmp);
     if (analyser->fd_here > 0)
        close(analyser->fd_here);
    waitpid(pid, &shell->exit_statut, 0);
    if (WEXITSTATUS(shell->exit_statut) == 130)
    {
       return (1) ; 
    }
    return 0;
}

int check_heredoc (t_shell * shell)
{
    t_command *analyser;
    t_redirect *tmp;
    analyser = shell->cmd;
    analyser->fd1_here = -1;
    analyser->fd_here = -1;
    while (analyser)
    {
        tmp = analyser->redirects;
        while  (tmp)
        {
            if (tmp->type == 3)
                if (type_three_heredoc(shell,analyser,tmp))
                    return 1;
            tmp = tmp->next;
        }
        analyser = analyser->next;
    }
    return 0;
}
#include "parsing_ali/minishell.h"

void close_Aff_fds(int i)
{
    struct   stat fds;
    while (i < 1024)
    {
        if (fstat(i, &fds) == 0)
            close(i);
        i++;
    }
}
void signal_handler_here_doc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    // free_all(var_ali());
    close_Aff_fds(3);
    exit(130);
}

void open_heredz(t_shell *shell, t_command * analyser)
{
    if (analyser->fd_here != -1)
    {
        close (analyser->fd_here);
        analyser->fd_here = -1;    
    }
    if (analyser->fd1_here != -1)
    {
        close (analyser->fd1_here);
        analyser->fd1_here = -1;    
    }
    analyser->fd_here = open(shell->rend.rnd_3,O_CREAT | O_WRONLY | O_TRUNC, 0644);
    analyser->fd1_here = open(shell->rend.rnd_3, O_RDONLY);
    if (  analyser->fd_here == -1 ||   analyser->fd1_here== -1 )
        perror("");
    unlink(shell->rend.rnd_3);
    // analyser->fd_in = dup(analyser->fd1_here);
    // close(analyser->fd1_here);
    
}
void child_fill_herd(t_command * analyser,t_redirect * tmp)
{
    char *line;
    close(analyser->fd1_here);
    if (analyser->fd_in)
        close(analyser->fd_in);
    signal(SIGINT, signal_handler_here_doc);
    while (1)
    {
        line = readline("herdoc > ");
        if (!line)
            break;
        if (ft_strcmp(line, tmp->delimiter) == 0)
            break;
        write(analyser->fd_here, line, ft_strlen(line));
        write(analyser->fd_here, "\n", 1);
        free(line);
    }
    close_Aff_fds(3);
    // close (analyser->fd_here);
    // close(analyser->fd_origin);
    // close(analyser->fd_origin_in);
    exit(0);
}

int trav_reds(t_shell * shell,t_command * analyser ,t_redirect * tmp)
{
    while  (tmp)
    {
        if (tmp->type == 3)
        {
            open_heredz(shell,analyser);
            int pid = fork();
            if (pid == 0)
            {
                child_fill_herd(analyser,tmp);
            }
            close(analyser->fd_here);
            analyser->fd_in = dup(analyser->fd1_here);
            close(analyser->fd1_here);
            //  if (analyser->fd_here > 0)
            //     close(analyser->fd_here);
            waitpid(pid, &shell->exit_statut, 0);
            if (WEXITSTATUS(shell->exit_statut) == 130)
            {
               return (1) ; 
            }
        }
        tmp = tmp->next;
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
        if (trav_reds(shell,analyser,tmp))
            return 1;
        analyser = analyser->next;
    }
    return 0;
}
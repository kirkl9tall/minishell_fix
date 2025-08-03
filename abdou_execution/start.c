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


// void signal_handler_child()
// {
    
//     exit(1);// must make exit status of ctrl +c 
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
}
void wait_childs(t_shell *shell, t_hp s)
{
    s.i = 0;
    while (s.i < s.nb_cmd)
    {
        waitpid(s.pid[s.i],&shell->exit_statut,0);
        s.i++;
    }
    if (WIFSIGNALED(shell->exit_statut))
    {
        if (WTERMSIG(shell->exit_statut) == 2 || WTERMSIG(shell->exit_statut) == 3)
        {
            if (WTERMSIG(shell->exit_statut) == 3)
                write (1, "Quit", 4);
            write(1, "\n", 1);
        }
    }
    if (s.p != -1)
            close(s.p);       
    s.pid = NULL;
}

void p_n_pipe(t_hp *s)
{
    if (s->p != -1)
        close(s->p);
    if (s->i < s->nb_cmd - 1)
    {
        close(s->pipe_fd[1]);
        s->p = s->pipe_fd[0];
    }   
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
        p_n_pipe(&s);
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
int fathers_command(t_shell *shell, t_command * cmd)
{
    int nbr_pipe;

    nbr_pipe = pipe_nbr(shell->cmd);
    if (nbr_pipe == 0)
    {
        if (redirecter(shell,cmd) == 1)
        {
            close_fds();
            return 0;
        }
        dup2(cmd->fd_out,1);
        dup2(cmd->fd_in,0);
        if (check_func_buil(shell,cmd) == 1)
            return 0;
    }
    return (1);
}

int start(t_shell *shell)
{
    // t_command *analyzer;
    // analyzer = shell->cmd;
    init_fds(shell);
    signal(SIGINT,SIG_IGN);
    if (check_heredoc(shell))
        return (0);
    int f = check_cmd(shell->cmd);
    if (!f)
    {
        close_fds();
        return 0;
    }
    if (!fathers_command(shell,shell->cmd))
        return 0;
    handle_pipes(shell);
    dup2(shell->cmd->fd_origin,1);
    dup2(shell->cmd->fd_origin_in,0);
    close(shell->cmd->fd_origin);
    close(shell->cmd->fd_origin_in);
    return 0;
}

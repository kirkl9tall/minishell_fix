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

t_ex_f	ft_atoi_exit(const char *str)
{
	int	i;
	int	sn;
	t_ex_f res;

	sn = 1;
	res.res = 0;
    res.flag = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sn = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res.res = res.res * 10 + (str[i] - '0');
		if (res.res > INT_MAX   || res.res < INT_MIN)
			res.flag = 1;
        i++;
	}
	res.res = res.res *sn;
	return (res);
}

void exit_numeric_required(t_command *cmd,t_shell *shell)
{
    ft_putstr_fd("exit\n",2);
    ft_putstr_fd(cmd->args[0],2);
    ft_putstr_fd(" : ",2);
    ft_putstr_fd(cmd->args[1],2);
    ft_putstr_fd(" : numeric argument required\n",2);
    close(shell->cmd->fd_origin);
    close(shell->cmd->fd_origin_in);
    free_env(shell->env);
    gr_t(NULL,1);
    exit(2);
}

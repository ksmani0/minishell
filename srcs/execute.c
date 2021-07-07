#include "minishell.h"

void    set_pipe(t_cmd *c_list)
{
    if (c_list->prev)
        dup2(c_list->prev->fds[0], g_data->stdin);
    if (c_list->pipe)
        dup2(c_list->fds[1], g_data->stdout);
}

int     none_fork_execute(t_cmd *c_list)
{
    char    *tmp;

    tmp = c_list->cmd->content;
    if (ft_strcmp(tmp, "cd") == 0)
        ft_cd(c_list);
    else if (ft_strcmp(tmp, "unset") == 0)
        ft_unset(c_list, g_data);
    else if (ft_strcmp(tmp, "export") == 0)
        ft_export(c_list, g_data);
    else if (ft_strcmp(tmp, "exit"))
        ft_exit(c_list, g_data);
}

void    fork_execute(t_cmd *c_list)
{
    pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		child_execute(c_list);
		exit(g_data->ret);
	}
	else
	{   
		waitpid(pid, &status, 0);
        close(c_list->fds[1]);
		if (WIFEXITED(status))
			g_data->ret = WEXITSTATUS(status);
	}
}

void	close_fd_dup(t_cmd *c_list)
{
    dup2(g_data->origin_stdin, g_data->stdin);
    dup2(g_data->origin_stdout, g_data->stdout);
}

void    execute(t_cmd *c_list)
{
    int pid;
    int status;

    if (check_redirection_list(c_list->r_list) == -1)
        return ;
    if (check_need_fork(c_list) == 1)
        fork_execute(c_list);
    else if (check_none_fork(c_list) == 1)
        none_fork_execute(c_list);
    else
        etc(c_list);
	close_fd_dup(c_list);
}
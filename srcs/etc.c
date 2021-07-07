#include "minishell.h"

static char     **make_argv(t_cmd *c_list, char *buf)
{
    int     i;
    char    **tmp;
    t_list  *cmd;

    cmd = c_list->cmd->next;
    i = 0;
    while(cmd)
    {
        cmd = cmd->next;
        i++;
    }
    tmp = (char **)malloc(sizeof(char *) * (i + 2));
    tmp[i + 1] = 0;
    i = 1;
    tmp[0] = ft_strdup(buf);
    cmd = c_list->cmd->next;
    while (cmd)
    {
        tmp[i] = ft_strdup(cmd->content);
        cmd = cmd->next;
        i++;
    }
    return (tmp);
}

void    execute_etc(t_cmd *c_list, char *buf)
{
    int		status;
    char    **argv;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
        set_pipe(c_list);
		set_rd(c_list->r_list);
        argv = make_argv(c_list, buf);
		if (execve(buf, argv, g_data->envp) < 0)
        {
            printf("bash: %s: %s\n", c_list->cmd->content, strerror(errno));
		    if (errno == 13)
			    exit(126);
		    else if (errno == 2)
			    exit(127);
            free_split(argv);
        }
	}
	else
	{
		waitpid(pid, &status, 0);
        close(c_list->fds[1]);
		if (WIFEXITED(status))
			g_data->ret = WEXITSTATUS(status);
	}
}

int             check_executable(char *buf, t_cmd *c_list)
{
    int     i;
    struct  stat sb;

    i = stat(buf, &sb);
    if (i != 0)
    {
		g_data->ret = 127;
        return (1);
    }
    else if (S_ISDIR(sb.st_mode))
    {
		g_data->ret = 126;
        return (2);
    }
    else
    {
        if (sb.st_mode & S_IXUSR)
            return (0);
        else
        {
            g_data->ret = 999;
            return (3); // permission denined
        }
    }
}

void            etc(t_cmd *c_list)
{
    char        *cmd;
    char        buf[5000];
    int         i;

    cmd = c_list->cmd->content;
    if (*cmd != '/')
    {
        //first implements pwd + join
        if (check_current_folder(c_list))
            return ;
        else if (check_path_folder(c_list))
            return ;
        else
            print_error(c_list);
    }
    else
    {
        if (check_executable(c_list->cmd->content, c_list) == 0)
            execute_etc(c_list, c_list->cmd->content);
        else
            print_error(c_list);
    }
}
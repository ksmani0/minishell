#include "minishell.h"

static void     check_executable(struct stat sb, int i, t_cmd *c_list, char *buf)
{
    if (i != 0)
    {
        printf("bash: %s: command not found\n", c_list->cmd->content);
		g_data->ret = 127;
        return ;
    }
    else if (S_ISDIR(sb.st_mode))
    {
        printf("bash: %s: is a directory\n", c_list->cmd->content);
		g_data->ret = 126;
        return ;
    }
    else
    {
        if (sb.st_mode & S_IXUSR)
            execute_etc(c_list, buf);
        else
            return ;
    }
}

static  void    execute_etc(t_cmd *c_list, char *buf)
{
    int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		set_rd(c_list->r_list);
		if (execve(buf, argv, envp) < 0)
        {
            printf("bash: %s: %s\n", c_list->cmd->content, strerror(errno));
		    if (errno == 13)
			    exit(126);
		    else if (errno == 2)
			    exit(127);
        }
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_data->ret = WEXITSTATUS(status);
	}
}

void            etc(t_cmd *c_list)
{
    struct stat sb;
    char        *cmd;
    char        buf[5000];
    int         i;

    cmd = c_list->cmd->content;
    if (ft_strchr(cmd, '/') == 0)
        i = stat(c_list->cmd->content, &sb);
    else
    {
        getcwd(buf, 5000);
        i = ft_strlen(buf);
        buf[i] = '/';
        ft_strlcpy((buf + i), cmd, ft_strlen(cmd) + 1);
        i = stat(buf, &sb);
    }
    check_executable(sb, i, c_list, buf);
}
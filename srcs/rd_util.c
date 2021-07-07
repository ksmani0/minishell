#include "minishell.h"

int     check_need_fork(t_cmd   *c_list)
{
    char    *tmp;

    tmp = c_list->cmd->content;
    if (ft_strcmp(tmp, "echo") == 0 || ft_strcmp(tmp, "env") == 0 || 
    ft_strcmp(tmp, "pwd") == 0)
    {
        return (1);
    }
    return (0);
}

int     check_none_fork(t_cmd   *c_list)
{
    char    *tmp;

    tmp = c_list->cmd->content;
    if (ft_strcmp(tmp, "cd") == 0 || ft_strcmp(tmp, "export") == 0 || 
    ft_strcmp(tmp, "unset") == 0 || ft_strcmp(tmp, "exit") == 0)
    {
        return (1);
    }
    return (0);
}

void    set_rd(t_rd *r_list)
{
    int     fd;

    while (r_list)
    {
        if (ft_strcmp(r_list->specific, ">>") == 0)
        {
            fd = open(r_list->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
            dup2(fd, g_data->stdout);
        }
        else if (*(r_list->specific) == '>')
        {
            fd = open(r_list->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            dup2(fd, g_data->stdout);
        }
        else if (*(r_list->specific) == '<')
        {
            fd = open(r_list->filename, O_RDONLY);
            dup2(fd, g_data->stdin);
        }
        r_list = r_list->next;
    }
}

int    check_redirection_list(t_rd  *r_list)
{
    int fd;
    while (r_list)
    {
        if (ft_strcmp(r_list->specific, ">>") == 0)
            fd = open(r_list->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
        else if (*(r_list->specific) == '>')
            fd = open(r_list->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        else if (*(r_list->specific) == '<')
            fd = open(r_list->filename, O_RDONLY);
        if (fd == -1)
        {
            printf("no such file or directory: %s\n", r_list->filename);
            return (-1);
        }
        r_list = r_list->next;
    }
    return (1);
}
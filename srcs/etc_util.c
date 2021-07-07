#include "minishell.h"

void    print_error(t_cmd *c_list)
{
    if (g_data->ret == 126)
        printf("%s: is a directory\n", c_list->cmd->content);
    else if (g_data->ret == 127)
        printf("%s: command not found\n", c_list->cmd->content);
    else if (g_data->ret == 999)
    {
        printf("permission denined: %s\n", c_list->cmd->content);
        g_data->ret = 126;
    }
}

bool    check_current_folder(t_cmd *c_list)
{
    struct stat sb;
    char        buf[5000];
    int         i;

    getcwd(buf, 5000);
    i = ft_strlen(buf);
    buf[i] = '/';
    ft_strlcpy((buf + i), c_list->cmd->content, ft_strlen(c_list->cmd->content) + 1);
    if (check_executable(buf, c_list) == 0)
    {
        execute_etc(c_list, buf);
        return (true);
    }
    return (false);
}

bool    check_path_folder(t_cmd *c_list)
{
    struct stat sb;
    int         i;
    char        buf[5000];
    char        *path_value;
    char        **paths;

    path_value = get_env_value("PATH");
    paths = ft_split(path_value, ':');
    while (*paths)
    {
        i = ft_strlen(*paths);
        ft_strlcpy(buf, *paths, ft_strlen(*paths) + 1);
        buf[i] = '/';
        ft_strlcpy((buf + i + 1), c_list->cmd->content, ft_strlen(c_list->cmd->content) + 1);
        if (check_executable(buf, c_list) == 0)
        {
            execute_etc(c_list, buf);
            return (true);
        }
        paths++;
    }
    return (false);
}
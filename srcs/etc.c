#include "minishell.h"

static bool     check_executable(struct stat sb)
{
    if (sb.st_mode & S_IXUSR)
        return (true);
    else
    {
        
    }
}

static  void    execute_etc(t_cmd *c_list, char *buf)
{

}

void            etc(t_cmd *c_list)
{
    struct stat sb;
    char        *cmd;
    char        buf[5000];
    int         i;

    cmd = c_list->cmd->content;
    if (ft_strchr(cmd, '/') == 0)
        stat(c_list->cmd->content, &sb);
    else
    {
        getcwd(buf, 5000);
        i = ft_strlen(buf);
        buf[i] = '/';
        ft_strlcpy((buf + i), cmd, ft_strlen(cmd) + 1);
        stat(buf, &sb);
    }
    if (check_executable(sb))
        execute_etc(c_list, buf);
}
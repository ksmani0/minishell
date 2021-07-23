#include "minishell.h"

void    handle_keycode(char **buf, char c)
{
    int     len;
    char    *tmp;
    
    if (*buf == 0)
    {
        tmp = (char *)malloc(2);
        *tmp = c;
        *(tmp + 1) = 0;
        *buf = tmp;
        return ;
    }
    len = ft_strlen(*buf) + 2;
    tmp = (char *)malloc(len);
    len = ft_strlen(*buf);
    ft_strlcpy(tmp, *buf, len + 1);
    tmp[len] = c;
    tmp[len + 1] = 0;
    free_buffer(buf);
    *buf = tmp;
}

void    fd_write(t_rd *next, char *buf, bool tf, char *filename)
{
    int     fd;

    if (!next)
    {
        fd = open("tmp", O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (tf)
            write(fd, buf, ft_strlen(buf) - ft_strlen(filename));
        else
            write(1, "invalid end\n", 12);
        close(fd);
        fd = open("tmp", O_RDONLY);
        g_data->herodoc_fd = fd;
        dup2(fd, g_data->stdin);
    }
    else
        free_buffer(&buf);
}

int     herodoc(char *filename, t_rd *next)
{
    char    *buf;
    int     read_byte;
    int     c;
    bool    tf;

    buf = 0;
    tf = false;
    write(1, "\n>", 2);
    while (read(0, &c, 1) > 0)
    {
        if (ft_strnstr(buf, filename, ft_strlen(buf)) != 0)
        {
            tf = true;
            break ;
        }
		if ((char)c == '\n')
			write(1, ">", 1);
		handle_keycode(&buf, c);
    }
    fd_write(next, buf, tf, filename);
}

void    delete_tmp(void)
{
    char pwd[5000];
    char *tmp;
    
    getcwd(pwd, 5000);
    tmp = ft_strjoin(pwd, "/tmp");
    unlink(tmp);
    free(tmp);
}
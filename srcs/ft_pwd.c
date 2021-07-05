#include "minishell.h"

void    ft_pwd(t_cmd *c_list)
{
    char    *buf;

    buf = getcwd(0, 5000);
	if (!buf)
		return ;
	else
		printf("%s\n", buf);
    free(buf);
}
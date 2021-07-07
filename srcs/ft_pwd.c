#include "minishell.h"

void    ft_pwd(t_cmd *c_list)
{
    char    *buf;

	set_pipe(c_list);
	set_rd(c_list->r_list);
    buf = getcwd(0, 5000);
	if (!buf)
		return ;
	else
		printf("%s\n", buf);
    free(buf);
}
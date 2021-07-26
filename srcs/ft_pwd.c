#include "minishell.h"

int    ft_pwd(t_cmd *c_list)
{
    char    *buf;

	g_data->ret = 0;
	set_pipe(c_list);
	set_rd(c_list->r_list);
    buf = getcwd(0, 5000);
	if (!buf)
		return (g_data->ret);
	else
		printf("%s\n", buf);
    free(buf);
	return (g_data->ret);
}
#include "minishell.h"

static  void    print_echo(t_list *tmp, int flag)
{
    char tmp2[3];

	tmp2[0] = '\\';
	tmp2[1] = 'n';
	tmp2[2] = 0;
    while (tmp && ft_strcmp(tmp->content, tmp2) != 0)
    {
        write(1, tmp->content, ft_strlen(tmp->content));
        tmp = tmp->next;
        if (tmp && ft_strcmp(tmp->content, tmp2) != 0)
            write(1, " ", 1);
    }
    if (flag)
        write(1, "\n", 1);
}

void            ft_echo(t_cmd *c_list)
{
    int     flag;
    int     size;
    t_list  *tmp;

    set_rd(c_list->r_list);
    tmp = c_list->cmd->next;
    size = ft_lstsize(c_list->cmd) - 1;
    flag = 1;
    if (size == 1)
        return ;
    else if ((my_strcmp(tmp->content, "-n") == 0))
    {
        if (size == 2)
            return ;
        tmp = tmp->next;
        flag = 0;
    }
    print_echo(tmp, flag);
}
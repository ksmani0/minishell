#include "minishell.h"

bool    is_same(char *a, char *b)
{
    if (ft_strlen(a) == ft_strlen(b))
    {
        if(ft_strcmp(a,b) == 0)
            return (true);
        else
            return (false);
    }
    else
        return (false);
}

void            delete_free(t_env *tmp)
{
    tmp->prev->next = tmp->next;
    if (tmp->next != 0)
        tmp->next->prev = tmp->prev;
    free_buffer(&tmp->key);
    free_buffer(&tmp->value);
    free(tmp);
}

void            delete_env(t_env *env_list, char *argv)
{
    t_env *tmp;

    tmp = env_list;
    while (tmp)
    {
        if (is_same(tmp->key, argv))
            delete_free(tmp);
        tmp = tmp->next;
    }
}

void            ft_unset(t_cmd *c_list, t_sh_data *g_data)
{
    int     size;
    t_list  *tmp;
    char tmp2[3];

	tmp2[0] = '\\';
	tmp2[1] = 'n';
	tmp2[2] = 0;
    set_rd(c_list->r_list);
    tmp = c_list->cmd;
    size = ft_lstsize(tmp) - 1;
    if (size == 0)
        printf("unset: not enough arguments\n");
    else
    {
        while (tmp && ft_strcmp(tmp->content, tmp2) != 0)
        {
            delete_env(g_data->env_list, tmp->content);
            tmp = tmp->next;
        }
    }
}
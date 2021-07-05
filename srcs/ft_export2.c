#include "minishell.h"

int     error_print(char *argv, char *value_index)
{
    if (argv == value_index)
    {
        printf("bash: export: `%s': not a valid identifier\n", argv);
	    g_data->ret = 1;
        return (1);
    }
    return (0);
}

void    check_delete_env(t_env * env_list, char *argv)
{
    if (get_env_value(argv) == 0)
    {
        delete_env(env_list, argv);
        env_add_back(&env_list, make_env(ft_strdup(argv), ft_strdup("")));
    }
}
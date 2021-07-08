#include "minishell.h"

void        my_sig_handle(int sig_number)
{
    if (sig_number == SIGINT)
    {
        if (g_data->forked == 0)
        {
            printf("\n$");
            rl_on_new_line();
            rl_replace_line("", 0);
        }
        else
        {
            write(1, "\n", 1);
        }
    }
    else if (sig_number == SIGQUIT)
    {
        printf("sig_quit\n");
    }
}
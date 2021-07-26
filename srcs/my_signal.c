#include "minishell.h"

void        sig_off(int sig_number)
{
    signal(SIGINT, main_signal);
    signal(SIGQUIT, main_signal);
}

void        main_signal(int sig_number)
{
    if (sig_number == SIGINT )
    {
		rl_replace_line("", 0);
        if(g_data->forked == 0)
			write(1, "\n$", 2);
        else
			write(1, "\n", 1);
		g_data->ret = 130;
		rl_redisplay();
    }
    else if (sig_number == SIGQUIT)
    {
        if (g_data->forked == 1)
        {
            write(1, "Quit\n", 5);
            kill(0, SIGKILL);
        }
    }
}
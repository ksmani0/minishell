#include "minishell.h"

char 	*get_input()
{
	char	**commands;
	char	**tmp2;

	g_data->input = readline("$");
	if (g_data->input)
	{
		if (check_parse_error(g_data->input) == -1)
		{
			g_data->ret = 2;
			return (0);
		}
		g_data->input = ft_trim(g_data->input, ' ');
		return (g_data->input);
	}
	return (void *)0;
}

void	init_term2()
{
	tcgetattr(STDIN_FILENO, &g_data->main_term);
	tcgetattr(STDIN_FILENO, &g_data->child_term);
	g_data->main_term.c_lflag &= ~ICANON;
	g_data->main_term.c_lflag &= ECHO;
	g_data->main_term.c_cc[VMIN] = 1;
	g_data->main_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_data->main_term);
	tgetent(NULL, "xterm");
	g_data->cl = tgetstr("cl", NULL);
	g_data->cm = tgetstr("cm", NULL);
	g_data->ce = tgetstr("ce", NULL);
}

t_sh_data	*init_setting(char **envp)
{
	g_data = (t_sh_data *)malloc(sizeof(t_sh_data));
	g_data->env_list = parse_env(envp);
	g_data->stdin = 0;
	g_data->stdout = 1;
	g_data->origin_stdin = dup(0);
	g_data->origin_stdout = dup(1);
	g_data->envp = envp;
	g_data->forked = 0;
	g_data->signal = 0;
	signal(SIGINT, main_signal);
	signal(SIGQUIT, main_signal);
	init_term2();
}

//"echo $haha\"$haha\"'haha'";
int main(int argc, char **argv, char **envp)
{
	int		state;

	(void)argc;
	(void)argv;
	init_setting(envp);
	while(true)
	{
		if ((g_data->input = get_input()) != 0)
		{
			state = parse_execute(g_data->input);
			if (g_data->input)
				add_history(g_data->input);
		}
		else
		{
			if (g_data->ret != 2)
				return (0);
		}
		free_buffer(&g_data->input);
	}
	return (0);
}

#include "minishell.h"

char 	*get_input()
{
	char	**commands;
	char	**tmp2;

	g_data->input = readline("");
	if (check_parse_error(g_data->input) == -1)
		return (0);
	g_data->input = ft_trim(g_data->input, ' ');
	return (g_data->input);
}

void	free_input(char **input)
{

}

void	init_term()
{
	struct termios	term;
	char			*cm;
	char			*ce;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
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
	signal(SIGINT, (void *)my_sig_handle);
	signal(SIGQUIT, (void *)my_sig_handle);
	init_term();
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
		write(0, "$", 1);
		if ((g_data->input = get_input()) != 0)
		{
			state = parse_execute(g_data->input);
			if (g_data->input)
				add_history(g_data->input);
		}
		free_buffer(&g_data->input);
	}
	return (0);
}




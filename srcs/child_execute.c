#include "minishell.h"

void	init_child_term()
{
	struct termios	term;
	char			*cm;
	char			*ce;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ICANON;
	term.c_lflag &= ECHO;
	term.c_cc[VMIN] = 100;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
}

void	rd_norm_pass(char *buf, char **command)
{
	*buf = **command;
	buf = buf + 1;
	*command = *command + 1;
}

void	child_execute(t_cmd *c_list)
{
	if (is_same(c_list->cmd->content, "pwd"))
		ft_pwd(c_list);
	else if (is_same(c_list->cmd->content, "env"))
		ft_env(c_list, g_data);
	else if (is_same(c_list->cmd->content, "echo"))
		ft_echo(c_list);
}

char		*get_env2(char **commands, int *j)
{
	int		size;
	char	tmp[1000];
	int		i;
	char	*tmp2;
	
	i = 0;
	tmp2 = *commands;
	size = get_env_len(*commands);
	*j = size;
	tmp2++;
	while (i < size)
	{
		tmp[i] = *tmp2;
		tmp2++;
		i++;
	}
	tmp[i] = 0;
	*commands = tmp2;
	return (get_env_value(tmp));
}
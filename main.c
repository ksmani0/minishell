#include "minishell.h"

char *get_input()
{
	char	*tmp;
	char	*tmp2;
	char	**commands;
	int		i;

	tmp2 = ft_strdup("");
	get_next_line(STDIN_FILENO, &tmp);
	commands = ft_split(tmp, ';');
	while (*commands)
	{
		tmp = ft_trim(*commands, ' ');
		commands++;
	}

	return tmp;
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	*env_list;
	(void)argc;
	(void)argv;
	(void)envp;

	env_list = parse_env(envp);
	while(true)
	{
		input = get_input();
	}
	return (0);
}

#include "minishell.h"

char **get_input()
{
	char	*tmp;
	char	**commands;
	char	**tmp2;
	int		i;

	tmp = ft_strdup("");
	get_next_line(STDIN_FILENO, &tmp);
	commands = ft_split(tmp, ';');
	tmp2 = commands;
	while (*commands)
	{
		*commands = ft_trim(*commands, ' ');
		//*commands = convert_quotes(*commands);
		commands++;
	}
	return (tmp2);
}

//"echo $haha\"$haha\"'haha'";
int main(int argc, char **argv, char **envp)
{
	char	**input;

	(void)argc;
	(void)argv;
	(void)envp;

	g_env_list = parse_env(envp);
	while(true)
	{
		write(0, "$", 1);
		input = get_input();
		if (*input)
			parse_execute(input);
	}
	return (0);
}

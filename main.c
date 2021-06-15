#include "minishell.h"

char *get_input()
{
	char	*tmp;
	char	*tmp2;
	char	**commands;
	int		i;

	tmp = ft_strdup("");
	get_next_line(STDIN_FILENO, &tmp);
	commands = ft_split(tmp, ';');
	while (*commands)
	{
		*commands = ft_trim(*commands, ' ');
		*commands = convert_quotes(*commands);
		commands++;
	}
	return tmp;
}

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	*tmp;
	char	*tmp2 = "echo $haha\"$haha\"'haha'";
	(void)argc;
	(void)argv;
	(void)envp;

	g_env_list = parse_env(envp);
	tmp = (char *)malloc(50);
	ft_strlcpy(tmp, tmp2, ft_strlen(tmp2)+1);
	ft_replace(&tmp, " ", "");
	while(true)
	{
		input = get_input();
	}
	return (0);
}

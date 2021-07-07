#include "minishell.h"

char **get_input()
{
	char	*tmp;
	char	**commands;
	char	**tmp2;
	t_list	*e_tmp;

	tmp = ft_strdup("");
	get_next_line(STDIN_FILENO, &tmp);
	if (check_parse_error(tmp) == -1)
		return (0);
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

void	free_input(char **input)
{

}

//"echo $haha\"$haha\"'haha'";
int main(int argc, char **argv, char **envp)
{
	char	**input;
	int		state;

	(void)argc;
	(void)argv;
	g_data = (t_sh_data *)malloc(sizeof(t_sh_data));
	g_data->env_list = parse_env(envp);
	g_data->stdin = 0;
	g_data->stdout = 1;
	g_data->envp = envp;
	while(true)
	{
		write(0, "$", 1);
		if ((input = get_input()) != 0)
		{
			while (*input)
			{
				state = parse_execute(*input);
				input++;
			}
		}
		free_input(input);
	}
	return (0);
}




#include "minishell.h"

char *get_input()
{
	char	*tmp;
	int		ret;
	char	buf[1024];
	char	*tmp2;

	tmp2 = ft_strdup("");
	while (ret = read(STDIN, buf, 1024) > 0)
	{
		if (ret > 0)
		{
			tmp = ft_strjoin(tmp2, buf);
			free_buffer(&tmp2);
		}
		else if (ret == -1)
			return (void *)0;
		else if (ret == 0)
			break;
		tmp2 = tmp;
	}
	return tmp;
}

int main(int argc, char **argv, char **envp)
{
	char *input;
	(void)argc;
	(void)argv;
	(void)envp;

	while(true)
	{
		input = get_input();
	}
	return (0);
}

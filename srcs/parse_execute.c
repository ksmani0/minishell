#include "minishell.h"

void	reset_buf(char *k)
{
	int i;

	if (k == 0)
		return ;
	i = 0;
	while (i < 9000)
	{
		k[i] = 0;
		i++;
	}
}

t_cmd	*make_cmd(char *command)
{
	char	buf[9000];
	char	*argv;
	t_cmd	*tmp;
	
	reset_buf(buf);
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	tmp->cmd = 0;
	tmp->argv_list = 0;
	while (*command)
	{
		argv = get_argv();
		if (tmp->cmd == 0)
			tmp->cmd = argv;
		else
			ft_lstadd_back(tmp->argv_list, ft_lstnew((void *)argv));
	}
}

void	parse_execute(char **commands)
{
	t_cmd *cmd;

	while (*commands)
	{
		cmd = make_cmd(*commands);
		execute_cmd(cmd);
	}
}
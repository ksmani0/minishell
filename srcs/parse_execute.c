#include "minishell.h"

t_list	*make_token_list(char *command)
{
	char	*argv;
	t_list	*tmp;
	
	tmp = 0;
	while (*command)
	{
		argv = get_token(&command);
		if (argv != 0)
			ft_lstadd_back(&(tmp), ft_lstnew((void *)argv));
	}
	argv = (char *)malloc(3);
	argv[0] = '\\';
	argv[1] = 'n';
	argv[2] = 0;
	ft_lstadd_back(&(tmp), ft_lstnew((void *)argv));
	return (tmp);
}

int		parse_execute(char *command)
{
	t_list	*tokens;
	t_cmd	*c_list;
	char	**tmp_command;
	char	**back_up;

	c_list = 0;
	tmp_command = ft_split(command, '|');
	back_up = tmp_command;
	while (*tmp_command)
	{
		if (*(tmp_command + 1) == 0)
			cmd_lstadd_back(&c_list, make_cmd(ft_strdup(*tmp_command), 0));
		else
			cmd_lstadd_back(&c_list, make_cmd(ft_strdup(*tmp_command), 1));
		tmp_command++;
	}
	free_split(back_up);
	while (c_list)
    {
		execute(c_list);
        c_list = c_list->next;
    }
	free_cmd(c_list);
}
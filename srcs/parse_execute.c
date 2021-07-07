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
	return (tmp);
}

int		parse_execute(char *command)
{
	t_list	*tokens;
	t_cmd	*c_list;
	char	**tmp_command;
	char	**back_up;
	t_cmd	*c_backup;

	c_list = 0;
	tmp_command = ft_split2(command, '|');
	back_up = tmp_command;
	while (*tmp_command)
	{
		if (*(tmp_command + 1) == 0)
			cmd_lstadd_back(&c_list, make_cmd(ft_strdup(*tmp_command), 0));
		else
			cmd_lstadd_back(&c_list, make_cmd(ft_strdup(*tmp_command), 1));
		tmp_command++;
	}
	c_backup = c_list;
	free_split(back_up);
	while (c_list && my_strcmp(c_list->cmd->content, "") != 0)
    {
		execute(c_list);
        c_list = c_list->next;
    }
	free_cmd(c_backup);
}
#include "minishell.h"

void	child_execute(t_cmd *c_list)
{
	if (is_same(c_list->cmd->content, "pwd"))
		ft_pwd(c_list);
	else if (is_same(c_list->cmd->content, "env"))
		ft_env(c_list, g_data);
	else if (is_same(c_list->cmd->content, "echo"))
		ft_echo(c_list);
}
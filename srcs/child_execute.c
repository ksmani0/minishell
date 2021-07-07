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
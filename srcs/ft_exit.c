#include "minishell.h"

int		    is_num_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static void norm_pass(char *b)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", b);
	exit(255);
}

void	    ft_exit(t_cmd *c_list, t_sh_data *g_data)
{
	int	ret;

	//set_pipe(c_list);
	set_rd(c_list->r_list);
	if ((ft_lstsize(c_list->cmd)) == 1)
	{
		printf("exit\n");
		exit(g_data->ret);
	}
	else if ((ft_lstsize(c_list->cmd)) == 2)
	{
		if (is_num_str(c_list->cmd->next->content))
		{
			ret = ft_atoi(c_list->cmd->next->content);
			printf("exit\n");
			exit(ret);
		}
		else
			norm_pass(c_list->cmd->next->content);
	}
	else
	{
		printf("bash: exit: too many arguments\n");
		g_data->ret = 1;
	}
}
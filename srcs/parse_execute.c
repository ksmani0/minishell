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

void	norm_by_pass(char *buf, char **command)
{
	if (**command == '|' || **command == '<')
	{
		*buf = **command;
		buf = buf + 1;
		*command = *command + 1;
	}
	else if (**command == '>')
	{
		if (**(command + 1) == '>')
		{
			*buf = '>';
			*(buf + 1) = '>';
			*command = *command + 2;
		}
		else
		{
			*buf = **command;
			buf = buf + 1;
			*command = *command + 1;
		}
	}
}

char	*get_token(char **command)
{
	char	buf[9000];
	int		i;

	reset_buf(buf);
	i = 0;
	if (**command == '|' || **command == '<' || **command == '>')
	{
		norm_by_pass(buf, command);
		return (ft_strdup(buf));
	}
	while (**command)
	{
		if (**command == ' ' || **command == '\t' || **command == '\n')
		{
			*command = *command + 1;
			break ;
		}
		buf[i++] = **command;
		*command = *command + 1;
	}
	if (*buf == 0)
		return (0);
	return (ft_strdup(buf));
}

t_cmd	*make_cmd(char *command)
{
	char	*argv;
	t_cmd	*tmp;
	
	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	tmp->cmd = 0;
	tmp->argv_list = 0;
	while (*command)
	{
		argv = get_token(&command);
		if (argv != 0)
			ft_lstadd_back(&(tmp->argv_list), ft_lstnew((void *)argv));
	}
	return (tmp);
}

void	parse_execute(char **commands)
{
	t_cmd *cmd;
	
	cmd = make_cmd(*commands);
	int k = 4;
	//execute_cmd(cmd);
}
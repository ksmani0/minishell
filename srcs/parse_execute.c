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
	t_list	*start;
	t_rd	*r_list;
	char	**tmp_command;
	
	r_list = 0;
	tmp_command = ft_split(command, '|');
	while (*tmp_command)
	{
		*tmp_command = ft_trim(*tmp_command, ' ');
		tokens = make_token_list(*tmp_command);
		make_redirection_list(tokens, &r_list);
		start = set_start(tokens);
		del_free_rd(tokens);
		if (*(tmp_command + 1) == 0)
			execute(r_list, start, 0);
		else
			execute(r_list, start, 1);
		tmp_command++;
	}
}
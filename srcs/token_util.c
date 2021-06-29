#include "minishell.h"

void	pipe_rd(char *buf, char **command)
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

void    find_qt(char *buf, char **command, char c)
{
    int i;

    i = 1;
    buf[0] = **command;
    *command = *command + 1;
    while (**command)
    {
        if (**command == c)
            break ;
        buf[i] = **command;
        *command = *command + 1;
        i++;
    }
    buf[i] = **command;
    *command = *command + 1;
}

void    none_specific(char *buf, char **command)
{
    int i;

    i = 0;
    while (**command)
    {
        if (**command == ' ' || **command == '\t' || **command == '\n')
		{
			*command = *command + 1;
			break ;
		}
        buf[i] = **command;
        *command = *command + 1;
        i++;
    }
}

char	*get_token(char **command)
{
	char	buf[9000];

	reset_buf(buf);
    while (**command == ' ')
        *command = *command + 1;
	if (**command == '|' || **command == '<' || **command == '>')
		pipe_rd(buf, command);
	else if (**command == '"')
		find_qt(buf, command, '"');
	else if (**command == '\'')
		find_qt(buf, command, '\'');
	else
		none_specific(buf, command);
	return (ft_strdup(buf));
}
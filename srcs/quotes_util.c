#include "minishell.h"

int			count_double_quotes(char **commands)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp == '"')
			break ;
		else if (*tmp == '$')
			count = count + count_env(&tmp);
		else
		{
			count++;
			tmp++;
		}
	}
	*commands = tmp + 1;
	return (count);
}

int			count_one_quotes(char **commands)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp== '\'')
			break;
		count++;
		tmp++;
	}
	*commands = tmp + 1;
	return (count);
}

void		convert_double_quotes(char **start, char **commands)
{
	char	*tmp;
	char	*env_value;

	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp == '"')
			break ;
		else if (*tmp == '$')
		{
			env_value = get_env(&tmp);
			ft_strlcpy(*start, env_value, ft_strlen(env_value) + 1);
		}
		else
		{
			**start = *tmp;
			*start = *start + 1;
			tmp++;
		}
	}
	*commands = (tmp++);
	return ;
}

void		convert_one_quotes(char *start, char **commands)
{
	char	*tmp;

	tmp = *commands;
	tmp++;
	while (*tmp)
	{
		if (*tmp== '\'')
			break;
		*start = *tmp;
		start++;
		tmp++;
	}
	*commands = tmp + 1;
	return ;
}

int			count_env(char **commands)
{
	int		size;
	char	tmp[1000];
	int		i;
	char	*tmp2;
	
	i = 1;
	tmp2 = *commands;
	size = get_env_len(*commands);
	tmp2++;
	while (i < size)
	{
		tmp[i] = *tmp2;
		tmp2++;
		i++;
	}
	tmp[i] = 0;
	*commands = tmp2;
	if (get_env_value(tmp) == 0)
		return (0);
	else
		return (ft_strlen(get_env_value(tmp)));
}
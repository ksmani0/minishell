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

int			count_env(char **commands)
{
	int		size;
	char	*tmp;
	char	*tmp2;
	
	tmp2 = *commands;
	size = get_env_len(*commands);
	if(!(tmp = (char *)malloc(size)))
		return (-1);
	tmp2++;
	ft_strlcpy(tmp, tmp2, size);
	tmp2 = tmp2 + size - 1;
	*commands = tmp2;
	if (get_env_value(tmp) == 0)
		return (0);
	else
		return (ft_strlen(get_env_value(tmp)));
}
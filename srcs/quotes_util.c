#include "minishell.h"

int			count_env(char *commands)
{
	int		size;
	char	*tmp;
	
	size = get_env_len(commands);
	if(!(tmp = (char *)malloc(size)))
		return (-1);
	commands++;
	ft_strlcpy(tmp, commands, size);
	if (get_env_value(tmp) == 0)
		return (0);
	else
		return (ft_strlen(get_env_value(tmp)));
}
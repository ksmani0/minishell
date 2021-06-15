#include "minishell.h"

// env_name count -> $haha = 4
int			get_env_len(char *commands)
{
	char	*tmp;
	bool	start_number;
	int		count;

	count = 1;
	start_number = ft_isdigit(*commands) == 1 ? true : false;
	tmp = commands;
	tmp++;
	while (*tmp)
	{
		if (!valid_env_name(*tmp, start_number))
			break ;
		count++;
		tmp++;
	}
	return (count);
}

// first character -> digit -> only digit
//            	   -> else -> digit, alpha, '_'
bool	valid_env_name(char c, bool start_number)
{
	if (start_number)
	{
		if (ft_isdigit(c) == 1)
			return (true);
		else
			return (false);
	}
	else
	{
		if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1 || c == '_')
			return (true);
		else
			return (false);
	}
}
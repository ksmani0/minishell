#include "minishell.h"

int			calc_malloc_count(char *commands)
{
	int count;

	count = 0;
	while (*commands)
	{
		if (*commands == '"')
		{
			count = count + count_double_quotes(&commands);
		}
		else if (*commands == '$')
		{
			count = count + count_env(commands);
		}
		else if (*commands == '\'')
		{
			count = count + count_one_quotes(&commands);
		}
		commands++;
		count++;
	}
	return (count);
}

char		*convert_quotes(char *commands)
{
	int	size;

	size = calc_malloc_count(commands);
	/*
	while (*commands)
	{
		if (*commands == '"')
			count = count + count_double_quotes(&commands);
		else if (*commands == '$')
			count = count + count_env(&commands);
		else if (*commands == '\'')
			count = count + count_one_quotes(&commands);
		commands++;
		count++;
	}
	*/
	return (void *)0;
}
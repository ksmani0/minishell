#include "minishell.h"

char		*get_env(char **commands)
{
	int		size;
	char	tmp[1000];
	int		i;
	char	*tmp2;
	
	i = 0;
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
	return (get_env_value(tmp));
}

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
			count = count + count_env(&commands);
		}
		else if (*commands == '\'')
		{
			count = count + count_one_quotes(&commands);
		}
		else
		{
			commands++;
			count++;
		}
	}
	return (count);
}

void	cmd_lstiter(t_list *lst)
{
	t_list	*tmp;
	char	*tmp2;

	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->content;
		tmp->content = convert_quotes(tmp->content);
		free(tmp2);
		tmp = tmp->next;
	}
}

char		*convert_quotes(char *commands)
{
	char	*env_value;
	char	*tmp;
	char	*tmp2;

	tmp = (char *)malloc(calc_malloc_count(commands) + 1);
	tmp[calc_malloc_count(commands)] = 0;
	if (calc_malloc_count(commands) == 0)
		return (tmp);
	tmp2 = tmp;
	while (*commands)
	{
		if (*commands == '"')
			convert_double_quotes(&tmp, &commands);
		else if (*commands == '$')
		{
			env_value = get_env(&commands);
			ft_strlcpy(tmp, env_value, ft_strlen(env_value) + 1);
		}
		else if (*commands == '\'')
			convert_one_quotes(tmp, &commands);
		else
			*tmp++ = *commands++;
	}
	return (tmp2);
}

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
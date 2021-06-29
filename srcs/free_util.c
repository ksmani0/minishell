#include "minishell.h"

void free_cmd(t_cmd	*cmd)
{

}

void free_split(char **splits)
{
	char	**tmp;

	tmp = splits;
	while (*splits)
	{
		free(*splits);
		splits++;
	}
	free(tmp);
}

void free_list(t_list *tmp)
{
	t_list	*tmp2;

	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = tmp2;
	}
}
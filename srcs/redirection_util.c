#include "minishell.h"

t_rd	*rd_lstnew(char *specific, char *filename)
{
	t_rd	*tmp;

	if (!(tmp = (t_rd *)malloc(sizeof(t_rd))))
		return (NULL);
	if (!specific)
	{
		tmp->specific = NULL;
		tmp->filename = NULL;
		tmp->next = NULL;
	}
	else
	{
		tmp->specific = ft_strdup(specific);
		tmp->filename = ft_strdup(filename);
		tmp->next = NULL;
	}
	return (tmp);
}

void	rd_lstadd_back(t_rd **lst, t_rd *new)
{
	if ((*lst) == NULL)
	{
		*lst = new;
	}
	else
	{
		rd_lstlast(*lst)->next = new;
	}
}

t_rd	*rd_lstlast(t_rd *lst)
{
	t_rd	*tmp;
	t_rd	*tmp2;

	if (lst == 0)
		return ((void *)0);
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	return (tmp2);
}
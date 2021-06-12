#include "minishell.h"

t_env	*env_last(t_env *lst)
{
	t_env	*tmp;
	t_env	*tmp2;

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

void	env_add_back(t_env **lst, t_env *new)
{
	if ((*lst) == NULL)
	{
		*lst = new;
	}
	else
	{
		env_last(*lst)->next = new;
	}
}

t_env	*parse_env(char **envp)
{
	t_env *env_list;
	t_env *tmp;
	char **splits;

	env_list = 0;
	while (*envp)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		splits = ft_split(*envp, '=');
		tmp->key = splits[0];
		tmp->value = splits[1];
		env_add_back(&env_list, tmp);
		envp++;
	}
	return (env_list);
}
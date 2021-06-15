#include "minishell.h"

char	*get_env_value(char *key)
{
	t_env	*tmp;

	tmp = g_env_list;
	while (tmp)
	{
		if(ft_strcmp(key, tmp->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (void *)0;
}

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
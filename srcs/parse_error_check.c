#include "minishell.h"

bool	check_filename_valid(char *str)
{
	char tmp[3];

	tmp[0] = '\\';
	tmp[1] = 'n';
	tmp[2] = 0;
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<") == 0 
		|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, ";") == 0 || ft_strcmp(str, tmp) == 0)
	{
		if (ft_strcmp(str, tmp) == 0)
			printf("parse error near by '\\n'\n");
		else
			printf("parse error near by '%s'\n", str);
		return (false);
	}
	return (true);
}

bool	check_redirect_parse(t_list *tmp)
{
	t_list	*tmp2;
	char 	*c;
	char	*d;

	tmp2 = tmp;
	while (tmp2)
	{
		c = (char *)tmp2->content;
		if (ft_strcmp(c, ">") == 0 || ft_strcmp(c, "<") == 0 || 
			ft_strcmp(c,">>") == 0)
		{
			d = (char *)tmp2->next->content;
			if (check_filename_valid(d) == false)
				return (false);
		}
		tmp2 = tmp2->next;
	}
	return (true);
}

bool	make_redirection_list(t_list *tmp, t_rd **r_list)
{
	t_list	*tmp2;
	char 	*c;
	char	*d;

	tmp2 = tmp;
	while (tmp2)
	{
		c = (char *)tmp2->content;
		if (ft_strcmp(c, ">") == 0 || ft_strcmp(c, "<") == 0 || 
			ft_strcmp(c,">>") == 0)
		{
			d = (char *)tmp2->next->content;
			rd_lstadd_back(r_list, rd_lstnew(c, d));
		}
		tmp2 = tmp2->next;
	}
	return (true);
}

int		check_parse_error(t_cmd	*cmd, t_rd **r_list)
{
	t_list *tmp;
	char	*c;

	tmp = cmd->argv_list;
	if (check_redirect_parse(tmp) == false)
		return (-1);
	make_redirection_list(tmp, r_list);
}
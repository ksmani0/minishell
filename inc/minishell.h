#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"

# define STDIN 0
typedef struct	s_cmd
{
	char	*cmd;

}				t_cmd;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env	*parse_env(char **envp);
#endif

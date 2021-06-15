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

t_env	*g_env_list;

t_env	*parse_env(char **envp);
char	*convert_quotes(char *commands);
bool	valid_env_name(char c, bool start_number);
int		get_env_len(char *commands);
char	*get_env_value(char *key);
int		count_env(char **commands);
int		count_double_quotes(char **commands);
int		count_one_quotes(char **commands);
#endif

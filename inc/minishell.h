#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"

# define STDIN 0
# define PARSE_ERROR -1
# define NO_SUCH_FILE -2

typedef struct 	s_rd
{
	char		*specific;
	char		*filename;
	struct s_rd	*next;
}				t_rd;

typedef struct	s_cmd
{
	char	*cmd;
	t_list	*argv_list;
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
int		parse_execute(char **commnads);
int		check_parse_error(t_cmd	*cmd, t_rd **r_list);
t_rd	*rd_lstlast(t_rd *lst);
void	rd_lstadd_back(t_rd **lst, t_rd *new);
t_rd	*rd_lstnew(char *specific, char *filename);
#endif

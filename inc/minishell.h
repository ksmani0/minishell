#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
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
	t_list			*cmd;
	struct s_rd		*r_list;
	bool			pipe;
	int				fds[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
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
int		parse_execute(char *commnads);
int		check_parse_error(char	*cmd);
t_rd	*rd_lstlast(t_rd *lst);
void	rd_lstadd_back(t_rd **lst, t_rd *new);
t_rd	*rd_lstnew(char *specific, char *filename);
void	free_rd(t_list *tmp);
t_list	*set_start(t_list *tmp);
t_list	*make_token_list(char *command);
void 	free_list(t_list *tmp);
bool	make_redirection_list(t_list *tmp, t_rd **r_list);
void	del_free_rd(t_list	*tmp);
void 	execute(t_cmd *c_list);
void	cmd_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd   *make_cmd(char *command, int pipe);
void 	free_split(char **splits);
void 	free_cmd(t_cmd	*cmd);
char	*get_env(char **commands);
void	convert_one_quotes(char **start, char **commands);
void	convert_double_quotes(char **start, char **commands);
void	cmd_lstiter(t_list *lst);
void	reset_buf(char *k);
char	*get_token(char **command);
#endif

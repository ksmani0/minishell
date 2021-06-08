NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc

LIBFT = libft.a
LIBFT_DIR = lib/libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
LIBFT_FLAGS = -L./$(LIBFT_DIR) -lft
CFLAGS += -I $(LIBFT_DIR)
CFLAGS += -I ./inc/

FILES = main \

SRCS = $(addprefix srcs/, $(addsuffix .c, $(FILES))) 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(C_OBJS)
	$(MAKE) -C ./lib/libft
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(LIBFT_FLAGS)
	
clean :
	$(MAKE) clean -C ./lib/libft
	rm -rf $(SURP)
	rm -f $(OBJS) $(C_OBJS)

fclean :
	$(MAKE) fclean -C ./lib/libft
	rm -f $(OBJS) $(C_OBJS) $(NAME)
	
re : fclean all

.PHONY: clean fclean all re bonus

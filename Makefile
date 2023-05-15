CC = cc

NAME = minishell

CFLAGS = -fsanitize=address #-Wall -Werror -Wextra

ENV = env/add_node.c \
	  env/get_env_list.c \
	  env/get_node.c \
	  env/new_node.c \
	  env/get_key.c \
	  env/get_value.c 

TOKENIZER = tokenizer/tokenizer.c \
			tokenizer/tokening.c \
			tokenizer/token_utils.c \
			tokenizer/get_token.c

BUILTINS = builtins/echo.c \
		   builtins/exit.c \
		   builtins/pwd.c \
		   builtins/cd.c \
		   builtins/env.c \
		   builtins/export.c \
		   builtins/unset.c

PARSER = parser/parser.c 

CFILES = $(ENV) \
		 $(TOKENIZER) \
		 $(BUILTINS) \
		 $(PARSER) \
		 minishell.c \
		 expander.c \

LIBFT = libft/libft.a

INCLUDES = -I./libft -I../minishell -I./env -I./builtins -I./tokenizer -I./parser

OBJECTS = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	$(CC) -lreadline $(INCLUDES) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	make clean -C libft
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re : fclean all 

.PHONY : all clean fclean re



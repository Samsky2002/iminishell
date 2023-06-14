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
			tokenizer/token_utils.c \
			#tokenizer/tokening.c \
			#tokenizer/get_token.c

BUILTINS = builtins/echo.c \
		   builtins/exit.c \
		   builtins/pwd.c \
		   builtins/cd.c \
		   builtins/env.c \
		   builtins/export.c \
		   builtins/unset.c

PARSER = parser/parser.c \
		 parser/arg_utils.c \
		 parser/node_utils.c \
		 parser/redirect_utils.c

EXPANDER = expander/expander.c

CFILES = $(ENV) \
		 $(TOKENIZER) \
		 $(BUILTINS) \
		 $(PARSER) \
		 $(EXPANDER) \
		 minishell.c \

LIBFT = libft/libft.a

INCLUDES = -Iincludes/

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



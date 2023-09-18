CC = cc

NAME = minishell

CFLAGS =  -Wall -Werror -Wextra

ENV = env/env.c \
	  env/get_env.c \
	  env/env_utils.c

TOKENIZER = tokenizer/tokenizer.c \
			tokenizer/token_utils.c \

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
		 parser/redirect_utils.c \

EXPANDER = expander/expander.c \
		   expander/expander_utils.c \
		   expander/expand_normal.c \
		   expander/expand_quotes.c \

EXEC = exec/exec.c \
	   exec/exec_utils.c \
	   exec/exec_prep.c \
	   exec/exec_redirect_utils.c \
	   exec/exec_here_doc.c \
	   exec/here_doc_utils.c \
	   exec/piping.c \
	   exec/exec_redirect.c \
	   exec/exec_child_utils.c \
	   exec/here_doc_expansion.c \
	   exec/exec_child.c 

ERROR = error/syntax_error.c

CFILES = $(ENV) \
		 $(TOKENIZER) \
		 $(ERROR) \
		 $(PARSER) \
		 $(EXPANDER) \
		 $(BUILTINS) \
		 $(EXEC) \
		 minishell.c \
		 minishell_utils.c

LIBFT = libft/libft.a

INCLUDES = -Iincludes/

OBJECTS = $(CFILES:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTS)
	make -C libft
	$(CC) $(INCLUDES) -L/goinfre/oakerkao/homebrew/opt/readline/lib $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline


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



NAME = minishell
 
SRCS = parsing/check_ambiguous.c \
       parsing/parsing_1_pipe_and_redirection.c \
       parsing/parsing_1_quote.c \
	   parsing/parsing_2_quote.c \
	   parsing/parsing_3_quote.c \
       parsing/parsing_4_quote.c \
       parsing/parsing_expansion_1.c \
       parsing/parsing_expansion_2.c \
       parsing/parsing_random.c \
       parsing/parsing_syntax_error.c.c \
       parsing/parsing_utils_2.c \
	   parsing/parsing_utils_1.c \
	   parsing/splite_random_1.c \
       parsing/set_input_list_1.c \
	   parsing/set_input_list_2.c \
       parsing/Tokenization.c \
	   parsing/splite_py_string.c \
	   parsing/garbage_collecter.c \
	   parsing/pars_herdoc.c \
		execution/start.c \
		execution/start_2.c \
		execution/heredoc.c \
		execution/built_1.c \
		execution/built_2.c \
		execution/built_3.c \
		execution/built_4.c \
		execution/built_5.c \
		execution/built_6.c \
		execution/built_7.c \
		execution/built_8.c \
		execution/built_9.c \
		execution/built_10.c \
		execution/exit_fun.c \
		execution/export_0.c \
		execution/export.c \
		execution/export_2.c \
		minishell.c \

OBJS = $(SRCS:.c=.o)

CC = cc -g
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I.
all: $(NAME)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) parsing/minishell.h
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS) -lreadline
	@echo "\033[1;32m Build \033[1;93m✓ COMPLETE ✓\033[0m"


clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "\033[1;32m🧹 Clean \033[1;93m✓ COMPLETE ✓\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "\033[1;31m🧨 Full Clean \033[1;93m✓ COMPLETE ✓\033[0m"


re: fclean all

.PHONY: all clean fclean re

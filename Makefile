NAME = minishell
 
SRCS = parsing_ali/check_ambiguous.c \
       parsing_ali/parsing_1_pipe_and_redirection.c \
       parsing_ali/parsing_1_quote.c \
	   parsing_ali/parsing_2_quote.c \
	   parsing_ali/parsing_3_quote.c \
       parsing_ali/parsing_4_quote.c \
       parsing_ali/parsing_expansion_1.c \
       parsing_ali/parsing_expansion_2.c \
       parsing_ali/parsing_random.c \
       parsing_ali/parsing_syntax_error.c.c \
       parsing_ali/parsing_utils_2.c \
	   parsing_ali/parsing_utils_1.c \
       parsing_ali/printf_resulth.c \
	   parsing_ali/splite_random_1.c \
       parsing_ali/set_input_list_1.c \
	   parsing_ali/set_input_list_2.c \
       parsing_ali/Tokenization.c \
	   parsing_ali/splite_py_string.c \
	   parsing_ali/garbage_collecter.c \
	   parsing_ali/pars_herdoc.c \
		abdou_execution/start.c \
		abdou_execution/piper.c \


OBJS = $(SRCS:.c=.o)

CC = cc -g
RM = rm -f
# CFLAGS = -Wall -Werror -Wextra -I. -fno-omit-frame-pointer -g
CFLAGS = -Wall -Werror -Wextra -I.
# LDFLAGS = -fsanitize=address
all: $(NAME)

$(OBJS): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
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

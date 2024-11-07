GREEN = \033[1;3;32m
RED = \033[1;3;31m
YELLOW=\033[1;3;33m
RESET = \033[0m
MAGENTA = \033[1;35m
BLUE = \033[34;1;3m

CC = cc
NAME = minishell

CFLAGS = -Wall -Wextra  -Werror -lreadline

SRC = minishell.c \
		./srcs/signals/signals.c \
		./srcs/parsing/parsing_quote.c \
		./srcs/parsing/parsing.c \
		./srcs/parsing/split_parsing.c \
		./srcs/parsing/split_parsing_2.c \
		./srcs/utils/command_utils.c \
		./srcs/utils/env_utils.c \
		./srcs/utils/node_utils.c \
		./srcs/utils/redirect_utils.c \
		./srcs/utils/utils_1.c \
		./srcs/utils/utils_2.c \
		./srcs/built_in/built_in_echo.c\
		./srcs/built_in/built_in_env_2.c\
		./srcs/built_in/built_in_env.c\
		./srcs/built_in/built_in_exit.c\
		./srcs/built_in/built_in.c\
		./srcs/execution/ft_helper_1.c\
		./srcs/execution/ft_helper_2.c\
		./srcs/execution/ft_helper_3.c\
		./srcs/execution/ft_helper_4.c\
		./srcs/execution/ft_helper_5.c\
		./srcs/execution/ft_helper_6.c\
		./srcs/execution/ft_exe.c\
		./srcs/execution/ft_start.c\
		./srcs/execution/ft_handle_child.c\
		./srcs/execution/ft_heredoc.c\
		./srcs/execution/ft_open_files.c\
		./srcs/execution/ft_split.c\
		./srcs/execution/ft_start_execution.c\
		./srcs/parsing/split_parsing_3.c \
		./srcs/parsing/helper.c \
		./srcs/utils/option_utils.c \
		./srcs/parsing/split_wilcard.c \
		./srcs/utils/itoa.c\
		./srcs/execution/ft_atoi_long.c\

LIB = ./include/minishell.h


OBJ = $(SRC:.c=.o)

all: $(NAME)
	@echo -n;

$(NAME): $(OBJ) $(LIB)
	@$(CC) $(CFLAGS) -o $@ $(OBJ)  -lreadline 
	@echo "$(GREEN)\t\t✓ $(NAME)$(RESET)"
	@echo "$(MAGENTA)Usage:\n\t$(YELLOW)./minishell$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	@rm -f $(OBJ) 
	@echo "$(RED)\t\t✓ deleted objects $(NAME)$(RESET)"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)\t\t✓ deleted $(NAME) $(NAME_BONUS)$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
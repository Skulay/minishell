NAME        = minishell

CC          = cc
CFLAGS      = -Iincludes -Ilibft -g
LDFLAGS     = -lreadline

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC_DIR     = src

SRCS =  $(SRC_DIR)/main/main.c \
        $(SRC_DIR)/cmd/cd.c \
        $(SRC_DIR)/cmd/echo.c \
        $(SRC_DIR)/cmd/env.c \
        $(SRC_DIR)/cmd/exit.c \
        $(SRC_DIR)/cmd/export.c \
        $(SRC_DIR)/cmd/pwd.c \
        $(SRC_DIR)/cmd/unset.c \
        $(SRC_DIR)/env/my_env.c \
        $(SRC_DIR)/env/shlvl.c \
        $(SRC_DIR)/expand/expand.c \
        $(SRC_DIR)/expand/utils.c \
        $(SRC_DIR)/expand/utils_args.c \
        $(SRC_DIR)/expand/utils_redir.c \
        $(SRC_DIR)/debug/debug_lexer.c \
        $(SRC_DIR)/debug/debug_ast.c \
        $(SRC_DIR)/debug/debug_env.c \
        $(SRC_DIR)/lexer/helper_type.c \
        $(SRC_DIR)/lexer/helper_type2.c \
        $(SRC_DIR)/lexer/lexer.c \
        $(SRC_DIR)/lexer/list_lexer.c \
        $(SRC_DIR)/parsing/parsing.c \
        $(SRC_DIR)/parsing/check_error.c \
        $(SRC_DIR)/parsing/add_argument.c \
        $(SRC_DIR)/parsing/utils_parsing.c \
        $(SRC_DIR)/struct/init_struct.c \
        $(SRC_DIR)/clean_up/free_tok.c \
        $(SRC_DIR)/clean_up/free_tab.c \
        $(SRC_DIR)/clean_up/free_cmd.c \
        $(SRC_DIR)/exec/exec.c 

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

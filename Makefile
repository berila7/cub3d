NAME			=	cub3D

CC			=	cc
CFLAGS			=	-Wall -Wextra -Werror -Iincludes

SRC_DIR			=	src
PARSING_DIR		=	$(SRC_DIR)/parsing
HELPERS_DIR		=	$(SRC_DIR)/helpers
LIBFT_DIR		=	$(SRC_DIR)/lib/libft
GNL_DIR			=	$(SRC_DIR)/lib/gnl

SRCS			=	$(SRC_DIR)/main.c $(PARSING_DIR)/parser.c $(PARSING_DIR)/init_map.c $(LIBFT_DIR)/ft_strrchr.c \
					$(LIBFT_DIR)/ft_strcmp.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
OBJS			=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) includes/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

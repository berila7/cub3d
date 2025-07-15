NAME			=	cub3D

CC			=	cc
CFLAGS			=	-Wall -Wextra -Werror -Iincludes

LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a

SRC_DIR			=	src
PARSING_DIR		=	$(SRC_DIR)/parsing
HELPERS_DIR		=	$(SRC_DIR)/helpers
LIB_DIR			=	$(SRC_DIR)/lib

SRCS			=	main.c $(PARSING_DIR)/parser.c
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

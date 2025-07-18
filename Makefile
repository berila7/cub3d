NAME			=	cub3D

CC			=	cc
CFLAGS			=	-Wall -Wextra -Werror -Iincludes

SRC_DIR			=	src
PARSING_DIR		=	$(SRC_DIR)/parsing
HELPERS_DIR		=	$(SRC_DIR)/helpers
UTILS_DIR		=	$(SRC_DIR)/lib/utils
GNL_DIR			=	$(SRC_DIR)/lib/gnl

SRCS			=	$(SRC_DIR)/main.c $(PARSING_DIR)/parser.c $(PARSING_DIR)/init_map.c $(PARSING_DIR)/map_validation.c \
					$(UTILS_DIR)/ft_strrchr.c \
					$(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_strlen.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
					$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_calloc.c $(UTILS_DIR)/ft_bzero.c $(UTILS_DIR)/ft_strlcpy.c \
					$(PARSING_DIR)/free.c
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

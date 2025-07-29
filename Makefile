NAME			=	cub3D

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -Iincludes -fsanitize=address -g

SRC_DIR			=	src
RAYCASTING_DIR	=	$(SRC_DIR)/raycasting
PARSING_DIR		=	$(SRC_DIR)/parsing
HELPERS_DIR		=	$(SRC_DIR)/helpers
UTILS_DIR		=	$(SRC_DIR)/lib/utils
GNL_DIR			=	$(SRC_DIR)/lib/gnl
MLX_DIR			=	$(SRC_DIR)/lib/MLX42

MLX_LIB			=	$(MLX_DIR)/build/libmlx42.a
MLX_FLAGS		=	-I$(MLX_DIR)/include/MLX42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/mnt/homes/$(USER)/.brew/opt/glfw/lib/"  -I"/mnt/homes/$(USER)/.brew/include"


RAYCASTING_SRCS	=	$(RAYCASTING_DIR)/game.c

SRCS			=	$(SRC_DIR)/main.c $(PARSING_DIR)/parser.c $(PARSING_DIR)/init_map.c $(PARSING_DIR)/map_validation.c \
					$(PARSING_DIR)/free.c $(PARSING_DIR)/init_utils.c\
					$(UTILS_DIR)/ft_strrchr.c $(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/gc_substr.c \
					$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_calloc.c $(UTILS_DIR)/ft_bzero.c $(UTILS_DIR)/ft_strlcpy.c \
					$(UTILS_DIR)/gc_split.c $(UTILS_DIR)/split_utils.c $(UTILS_DIR)/gc_strdup.c $(UTILS_DIR)/ft_strncmp.c\
					$(HELPERS_DIR)/gc.c \
					$(RAYCASTING_SRCS) \
					$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
OBJS			=	$(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(MLX_DIR):
	@echo "Cloning MLX Library"
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build -Wno-dev && cmake --build build -j4

$(NAME): $(OBJS) includes/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

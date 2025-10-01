NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus

CC				=	cc
FLAGS			=	-Wall -Wextra -Werror
CFLAGS			=	$(FLAGS) -Imandatory/includes
CFLAGS_B		=	$(FLAGS) -Ibonus/includes

SRC_DIR			=	src
RC_DIR			=	mandatory/$(SRC_DIR)/raycasting
PARSING_DIR		=	mandatory/$(SRC_DIR)/parsing
RC_DIR_B		=	bonus/$(SRC_DIR)/raycasting
PARSING_DIR_B	=	bonus/$(SRC_DIR)/parsing
UTILS_DIR		=	lib/utils
GNL_DIR			=	lib/gnl
MLX_DIR			=	lib/MLX42

MLX_LIB			=	$(MLX_DIR)/build/libmlx42.a
MLX_FLAGS		=	-I$(MLX_DIR)/include/MLX42 -lm -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/mnt/homes/$(USER)/.brew/opt/glfw/lib/" -I"/mnt/homes/$(USER)/.brew/include"


RC_SRCS			=	$(RC_DIR)/game.c $(RC_DIR)/helpers.c $(RC_DIR)/point.c $(RC_DIR)/draw.c $(RC_DIR)/raycast.c \
					$(RC_DIR)/render_walls.c $(RC_DIR)/draw_utils.c $(RC_DIR)/helpers2.c $(RC_DIR)/textures.c $(RC_DIR)/textures_helpers.c

RC_SRCS_B		=	$(RC_DIR_B)/game_bonus.c $(RC_DIR_B)/movement_bonus.c $(RC_DIR_B)/helpers_bonus.c $(RC_DIR_B)/point_bonus.c $(RC_DIR_B)/draw_bonus.c \
					$(RC_DIR_B)/raycast_bonus.c $(RC_DIR_B)/render_walls_bonus.c $(RC_DIR_B)/draw_utils_bonus.c \
					$(RC_DIR_B)/helpers2_bonus.c $(RC_DIR_B)/textures_bonus.c $(RC_DIR_B)/player_bonus.c $(RC_DIR_B)/textures_helpers_bonus.c

SRCS			=	mandatory/$(SRC_DIR)/main.c $(PARSING_DIR)/parser.c $(PARSING_DIR)/init_map.c $(PARSING_DIR)/map_validation.c \
					$(PARSING_DIR)/init_utils.c $(PARSING_DIR)/helpers.c\
					$(UTILS_DIR)/ft_strrchr.c $(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/gc_substr.c \
					$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_calloc.c $(UTILS_DIR)/ft_bzero.c $(UTILS_DIR)/ft_strlcpy.c \
					$(UTILS_DIR)/gc_split.c $(UTILS_DIR)/split_utils.c $(UTILS_DIR)/ft_strncmp.c $(UTILS_DIR)/ft_itoa.c\
					$(UTILS_DIR)/ft_atoi.c $(UTILS_DIR)/ft_isdigit.c $(UTILS_DIR)/gc_split_char.c $(UTILS_DIR)/gc.c \
					$(RC_SRCS) \
					$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

SRCS_B			=	bonus/$(SRC_DIR)/main_bonus.c $(PARSING_DIR_B)/parser_bonus.c $(PARSING_DIR_B)/init_map_bonus.c \
					$(PARSING_DIR_B)/map_validation_bonus.c $(PARSING_DIR_B)/init_utils_bonus.c $(PARSING_DIR_B)/helpers_bonus.c\
					$(UTILS_DIR)/ft_strrchr.c $(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_strlen.c $(UTILS_DIR)/gc_substr.c $(UTILS_DIR)/ft_itoa.c\
					$(UTILS_DIR)/ft_strdup.c $(UTILS_DIR)/ft_calloc.c $(UTILS_DIR)/ft_bzero.c $(UTILS_DIR)/ft_strlcpy.c \
					$(UTILS_DIR)/gc_split.c $(UTILS_DIR)/split_utils.c $(UTILS_DIR)/ft_strncmp.c \
					$(UTILS_DIR)/ft_atoi.c $(UTILS_DIR)/ft_isdigit.c $(UTILS_DIR)/gc_split_char.c $(UTILS_DIR)/gc.c \
					$(RC_SRCS_B) \
					$(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_B:.c=.o)

all: $(MLX_LIB) $(NAME)
bonus: $(MLX_LIB) $(NAME_BONUS)

$(MLX_DIR):
	@echo "Cloning MLX Library"
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build -Wno-dev && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

mandatory/src/%.o: mandatory/src/%.c mandatory/includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS_B) $(OBJS_BONUS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME_BONUS)

bonus/src/%_bonus.o: bonus/src/%_bonus.c bonus/includes/cub3d_bonus.h
	$(CC) $(CFLAGS_B) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)

re: fclean all
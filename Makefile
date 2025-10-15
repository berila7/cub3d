NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS_M		=	$(CFLAGS) -Imandatory/includes
CFLAGS_B		=	$(CFLAGS) -Ibonus/includes


LIBFT_DIR		=	lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a

SRC_DIR			=	src
RC_DIR			=	mandatory/$(SRC_DIR)/raycasting
PARSING_DIR		=	mandatory/$(SRC_DIR)/parsing
RC_DIR_B		=	bonus/$(SRC_DIR)/raycasting
PARSING_DIR_B	=	bonus/$(SRC_DIR)/parsing
UTILS_DIR		=	utils
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
					$(PARSING_DIR)/init_utils.c $(PARSING_DIR)/helpers.c \
					mandatory/$(UTILS_DIR)/gc_split_char.c \
					mandatory/$(UTILS_DIR)/count_char.c mandatory/$(UTILS_DIR)/atoi_valid.c \
					$(RC_SRCS)

SRCS_B			=	bonus/$(SRC_DIR)/main_bonus.c $(PARSING_DIR_B)/parser_bonus.c $(PARSING_DIR_B)/init_map_bonus.c \
					$(PARSING_DIR_B)/map_validation_bonus.c $(PARSING_DIR_B)/init_utils_bonus.c $(PARSING_DIR_B)/helpers_bonus.c \
					bonus/$(UTILS_DIR)/count_char_bonus.c bonus/$(UTILS_DIR)/gc_split_char_bonus.c bonus/$(UTILS_DIR)/atoi_valid_bonus.c \
					$(RC_SRCS_B)

OBJS			=	$(SRCS:.c=.o)
OBJS_BONUS		=	$(SRCS_B:.c=.o)

all: $(LIBFT_DIR) $(MLX_LIB) $(NAME)
bonus: $(LIBFT_DIR) $(MLX_LIB) $(NAME_BONUS)

$(LIBFT_DIR):
	@make -C $(LIBFT_DIR)

$(MLX_DIR):
	@echo "Cloning MLX Library"
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build -Wno-dev && cmake --build build -j4

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS_M) $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

mandatory/%.o: mandatory/%.c mandatory/includes/cub3d.h
	$(CC) $(CFLAGS_M) -c $< -o $@


$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS_B) $(OBJS_BONUS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME_BONUS)

bonus/%_bonus.o: bonus/%_bonus.c bonus/includes/cub3d_bonus.h
	$(CC) $(CFLAGS_B) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_BONUS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: $(LIBFT_DIR)
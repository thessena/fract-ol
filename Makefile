NAME = fract-ol

RED := \033[31m
GREEN := \033[32m

CC = gcc
LIBMLX = ./mlx42/build

CFLAGS = -Wall -Wextra -Werror -g -Iinc -Imlx42/include
LDFLAGS = -L$(LIBMLX) -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw

SRC = src/main.c
OBJ = $(SRC:.c=.o)

MLX_DIR = mlx42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLXFT_LIB = ./mlx42/build/libmlx42.a

$(MLX_LIB):
	@rm -rf $(MLX_BUILD_DIR)
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_DIR) && cmake -B $(MLX_BUILD_DIR) && cmake --build $(MLX_BUILD_DIR)
	@echo "$(GREEN)MLX42 built successfully$(X)"

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) built successfully$(X)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)objects deleted$(X)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)fract-ol deleted$(X)"

re: fclean all

.PHONY: all clean fclean re

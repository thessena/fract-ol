NAME = fract-ol

BLACK := \033[30m
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
X := \033[0m

CC = gcc
LIBMLX = ./mlx42/build

CFLAGS = -Wall -Wextra -Werror -g -Iinc
LDFLAGS = -L$(LIBMLX) -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw

SRC = src/main.c
OBJ = $(SRC:.c=.o)

MLX_DIR = mlx42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a

$(MLX_LIB):
	@rm -rf $(MLX_DIR)
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
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
	@rm -rf $(MLX_BUILD_DIR)
	@echo "$(RED)fract-ol deleted$(X)"

re: fclean all

.PHONY: all clean fclean re
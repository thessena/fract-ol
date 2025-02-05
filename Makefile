# all -> baue dein objects, linke und mache eine binray MLX bauen
# re -> fclean all
# clean -> object files weg
# fclean -> clean und binaries weg   MLX weg

NAME = fractol

BLACK := \033[30m
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
X := \033[0m

CC = gcc
LIBMLX = /libs/MLX42/build

CFLAGS = -Wall -Wextra -Werror -g -Iinc
LDFLAGS = -L$(LIBMLX) -lmlx42 -lX11 -lXext -lm

SRC = src/main.c
OBJ = $(SRC:.c=.o)

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# MLX Variables
MLXFT_DIR=./mlx42
MLXFT=libmlx42.a
MLXFT_BUILD_FLAGS=-B
MLXFT_BUILD_DIR=./mlx42/build
MLXFT_LIB=$(MLXFT_BUILD_DIR)/$(MLXFT)
MLXFTFLAGS=-L$(MLXFT_BUILD_DIR) -lmlx42 -lglfw

$(MLXFT_LIB):
	@rm -rf mlx42
	@git clone https://github.com/codam-coding-college/MLX42.git mlx42
	@mkdir -p $(MLXFT_BUILD_DIR)
	@cd $(MLXFT_DIR) && cmake $(MLXFT_BUILD_FLAGS) ../$(MLXFT_BUILD_DIR) && cd .. && cd $(MLXFT_BUILD_DIR) && $(MAKE)
	@echo "$(GREEN)MLX42 built successfully$(X)"

all: $(MLXFT_LIB) 
	cc ./src/main.c $(MLXFTFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iinc -c $< -o $@

clean:
	@rm -rf mlx42
	@rm -rf $(OBJ_DIR)
	@rm -rf $(MLXFT_BUILD_DIR)
	# @$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)objects deleted$(X)"

fclean: clean
	rm -rf $(MLXFT_BUILD_DIR)
	@rm -rf $(NAME)
	# @$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)fract-ol deleted$(X)"

re: fclean all

.PHONY: all clean fclean re
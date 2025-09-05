# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thessena <thessena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 11:32:14 by thessena          #+#    #+#              #
#    Updated: 2025/09/05 13:44:10 by thessena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fract-ol

RED := \033[31m
GREEN := \033[32m

CC = gcc

MLX_DIR = mlx42
MLX_BUILD_DIR = $(MLX_DIR)/build
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a
MLX_URL = https://github.com/codam-coding-college/MLX42.git

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    SYS_LDFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
else
    SYS_LDFLAGS = -lglfw -ldl -lm -lpthread
endif

CFLAGS = -Wall -Wextra -Werror -g -Iinc -I$(MLX_DIR)/include
LDFLAGS = -L$(MLX_DIR)/build -lmlx42 $(SYS_LDFLAGS)

SRC = \
    src/main.c \
    src/app.c \
    src/args.c \
    src/render.c \
    src/input.c \
	src/input_scroll.c \
    src/color_utils.c \
	src/palette.c

OBJ = $(SRC:.c=.o)

all: $(NAME)


mlx_clone:
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		printf "Cloning MLX42...\n"; \
		git clone $(MLX_URL) $(MLX_DIR); \
	else \
		printf "MLX42 already present.\n"; \
	fi


$(MLX_LIB): mlx_clone
	@rm -rf $(MLX_BUILD_DIR)
	@mkdir -p $(MLX_BUILD_DIR)
	@cd $(MLX_DIR) && cmake -B build && cmake --build build
	@echo "$(GREEN)MLX42 built successfully$(X)"

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

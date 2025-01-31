NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = fractol.c
OBJ = $(SRC:.c=.o)
MLX = minilibx-linux

all: $(NAME)

$(NAME): $(OBJ)
    $(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(MLX) -lmlx -lX11 -lXext -lm

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re: fclean all

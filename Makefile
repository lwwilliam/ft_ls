NAME = ft_ls

SRCS = main.c parser.c color.c sub_dir.c sort.c list_print.c error.c non_dir.c

OBJ_DIR = ./obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	gcc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

# valgrind --leak-check=full \
#          --show-leak-kinds=all \
#          --track-origins=yes \
#          --verbose \
#          --log-file=valgrind-out.txt \
#          ./ft_ls .
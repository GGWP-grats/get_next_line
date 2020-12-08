NAME = gnl
SRC = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRC:.c=.o)
CCW = gcc -Wall -Wextra -Werror -g
LIB = libft/libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CCW) $(OBJ) $(LIB) -o gnl
	

$(LIB):
	make -C libft/
	make bonus -C libft/

%.o: %.c
	$(CCW) -c $< -o $@
clean:
	@make clean -C libft/ 
	@rm -rf *.o

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME)

re: fclean all

.PHONY: re clean clean libft.a $(NAME) all

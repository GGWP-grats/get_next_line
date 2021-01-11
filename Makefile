NAME = gnl
SRC = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRC:.c=.o)
CCW = gcc -Wall -Wextra -Werror -g 
BUFFER_SIZE = -D BUFFER_SIZE=$(BUF)
all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CCW) $(OBJ) -o gnl

f: $(LIB) $(OBJ)
	$(CCW) -fsanitize=address -fstack-protector $(OBJ) -o gnl


$(LIB):
	make -C libft/
	make bonus -C libft/

%.o: %.c
	$(CCW) $(BUFFER_SIZE) -c $< -o $@
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

ref: fclean f
.PHONY: re clean clean libft.a $(NAME) all

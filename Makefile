NAME = gnl
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
CCW = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): libft.a $(OBJ)
	$(CCW) $(OBJ) libft/libft.a -o gnl.out
	

libft.a:
	make -C libft/
	make bonus -C libft/
	make clean -C libft/

%.o: %.c
	$(CCW) -c $<  -o $@
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: re clean clean libft.a $(NAME) all

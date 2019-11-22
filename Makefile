EXE = lem-in
CC = gcc
CFLAG = -Wall -Werror -Wextra
LIB = libft/libft.a
PATH_LIB = /Users/pauljull/

SRC =	ft_recover_data.c \
		lem_in.c \
		ft_parsing.c \
		ft_parser_utils.c \

OBJ = $(SRC:.c=.o)
PATH_SRC = $(addprefix src/, $(SRC))
PATH_OBJ = $(addprefix obj/, $(OBJ))

all: libft_comp $(EXE)

libft_comp:
	make -C libft

$(EXE) : $(PATH_OBJ)
	$(CC) $(CFLAG) -I $(PATH_LIB) -o $(EXE) $(PATH_OBJ) $(LIB)

$(addprefix obj/, %.o): $(addprefix src/, %.c)
	$(CC) $(CFLAG) -c $< -o $@

lib_clean:
	make clean -C libft/

lib_fclean:
	make fclean -C libft/

clean: lib_clean
	rm -f $(PATH_OBJ)

fclean: lib_fclean clean
	rm -f $(EXE)

re: fclean all

.PHONY : libft clean fclean re comp lib_clean lib_fclean

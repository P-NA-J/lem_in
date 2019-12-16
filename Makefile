EXE = lem-in
CC = gcc 
CFLAG = -Wall -Werror -Wextra -g3 -fsanitize=address,undefined
LIB = libft/libft.a

SRC =	parser.c 				\
		main.c 					\
		ft_parsing.c 			\
		jenkins_hash.c			\
		preparser.c				\
		preparser_utils.c		\
		adjacency_matrix.c		\
		get_rooms.c				\
		ft_parser_utils.c 		\
		print_info.c			\
		ft_debug.c				\
		ft_bfs.c				\
		ft_mult_bfs.c			\
		return_error.c			\


OBJ = $(SRC:.c=.o)
PATH_SRC = $(addprefix src/, $(SRC))
PATH_OBJ = $(addprefix obj/, $(OBJ))

all: libft_comp $(EXE)

libft_comp:
	make -C libft

$(EXE) : $(PATH_OBJ)
	$(CC) $(CFLAG)  -o $(EXE) $(PATH_OBJ) $(LIB)

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

visu:
	 @#pip install --user networkx
	 @#pip install --user plotly==4.3.0
	 @#pip install --user chart-studio
	 @$(CC) $(LIB) visu/test.c -o grapher
	 @./grapher < visu/medium_res.txt | python visu/visualizer.py
	 @./grapher < visu/small.anthills | python visu/visualizer.py

GREEN   = '\x1b[32m'
RED     = '\x1b[31m'
END     = '\x1b[0m'

.PHONY : libft clean fclean re comp lib_clean lib_fclean visu

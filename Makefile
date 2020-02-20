EXE = lem-in
CC = gcc 
CFLAG = -Wall -Werror -Wextra -g3 -fsanitize=address,undefined
LIB = libft/libft.a

SRC =	main.c 						\
		alban/parser.c 				\
		alban/parser_utils.c		\
		alban/jenkins_hash.c		\
		alban/preparser.c			\
		alban/preparser_utils.c		\
		alban/links_tab.c			\
		alban/adjacency_matrix.c	\
		alban/get_rooms.c			\
		alban/print_info.c			\
		alban/return_error.c		\
		paul/ft_bfs.c				\
		paul/ft_path.c				\
		paul/ft_bhandari.c			\
		paul/ft_matrix_modif.c		\
		paul/ft_matrix_check.c		\
		paul/ft_queue.c				\
		paul/ft_initialisation.c	\
		paul/ft_buffer.c			\
		paul/ft_clean.c				\
		paul/ft_print.c				\
		paul/ft_bubble_sort.c		\
		paul/ft_snapshot.c			\
		paul/ft_debug.c				\
		paul/ft_evaluate_snapshot.c	\
		paul/ft_static_tab_utils.c	\

OBJ = $(SRC:.c=.o)
PATH_SRC = $(addprefix src/, $(SRC))
PATH_OBJ = $(addprefix obj/, $(OBJ))
PATH_HEADERS = $(addprefix includes/, $(HEADERS))

all: libft_comp $(EXE)

libft_comp:
	@make -C libft

$(EXE) : $(PATH_OBJ)
	@$(CC) $(CFLAG)  -o $(EXE) $(PATH_OBJ) $(LIB)

$(addprefix obj/, %.o): $(addprefix src/, %.c)
	@$(CC) $(CFLAG) -c $< -o $@

lib_clean:
	@make clean -C libft/

lib_fclean:
	@make fclean -C libft/

clean: lib_clean
	@rm -f $(PATH_OBJ)

fclean: lib_fclean clean
	@#brew install mpg123
	@mpg123 -q misc/chest_sound.mp3 misc/kanmem2.mp3 &
	@python misc/closed_chest.py
	@rm -f $(EXE)
	@sleep 6.66
	@clear
	@python misc/open_chest.py

re: fclean all

test: $(EXE)
	bash launch_test.sh

visu:
	 @#pip install --user networkx
	 @#pip install --user plotly==4.3.0
	 @#pip install --user chart-studio
	 @$(CC) $(LIB) visu/test.c -o grapher
#	 @./grapher < visu/medium_res.txt | python visu/visualizer.py
	 @./grapher < visu/small.anthills | python visu/visualizer.py

GREEN   = '\x1b[32m'
RED     = '\x1b[31m'
END     = '\x1b[0m'

.PHONY : libft clean fclean re comp lib_clean lib_fclean visu

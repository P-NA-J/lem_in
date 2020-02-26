EXE = lem-in
CC = gcc 
CFLAG = -Wall -Werror -Wextra
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
		paul/ft_evaluate_snapshot.c	\
		paul/ft_static_tab_utils.c	\
		paul/ft_queue_utils.c		\
		paul/ft_link_management.c	\
		paul/ft_free.c				\

OBJ = $(SRC:.c=.o)
PATH_SRC = $(addprefix src/, $(SRC))
PATH_OBJ = $(addprefix obj/, $(OBJ))
PATH_HEADERS = $(addprefix includes/, $(HEADERS))

all: libft_comp $(EXE)

libft_comp:
	@if ! [ -d "obj/" ]; then mkdir obj obj/alban obj/paul; fi
	@make -C libft

$(EXE) : libft_comp $(PATH_OBJ)
	@$(CC) $(CFLAG) -o $(EXE) $(PATH_OBJ) $(LIB)

$(addprefix obj/, %.o): $(addprefix src/, %.c)
	@$(CC) $(CFLAG) -c $< -o $@

lib_clean:
	@make clean -C libft/

lib_fclean:
	@make fclean -C libft/

clean: lib_clean
	@rm -f $(PATH_OBJ)

fclean: lib_fclean clean
	@rm -f $(EXE)

re: fclean all

.PHONY : libft clean fclean re comp lib_clean lib_fclean

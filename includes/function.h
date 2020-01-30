/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:51:52 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 19:02:33 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H

# define FUNCTION_H

typedef int	t_bool;

/*
	Fonctions liées au parsing.
*/

t_map		*parser(void);
t_preparse	*pre_parser(void);
uint32_t	jenkins_hash(char *name);
t_room		*get_next_room(t_preparse *prep, t_map *data);
t_room		**get_rooms(t_map *data, t_preparse *prep);
t_room		*parse_comment(t_preparse *prep, t_map *data);
int			get_pipes(t_map **data, t_preparse *prep);
int			end_or_start(t_preparse *prep, t_room *stend, t_map *data);
int			valid_coords(char *buffer);

t_map		*which_error(t_map *data, int type);
void		free_all(t_map *data);
char		*ft_passing_name(char *str);
char		*ft_strcsub(char *s, char c);
int			count_char_until(char *str, char c, char u);


/*
	Fonctions pour la matrice d'adjacence.
*/

int			ft_line_check(int *line, int len);
int			ft_path_length_matrix(int **adj_mat, t_map *data, int c_index);
void		ft_reset_matrix(t_map *data, int **adj_mat);
int			ft_check_line(int *line, int len, int nb);
int			**ft_mat_mirror_change(int **adj_mat, int value, int i_1, int i_2);
void		ft_clean_matrix(t_map *data, int **adj_mat);


/*
	Fonctions de gestion de la queue.
*/

t_room		*ft_remove_queue(t_queue *bfs_queue);
void		ft_add_queue(t_queue *bfs_queue, t_room *to_add, t_room *current, int time);
void		ft_add_front_queue(t_queue *bfs_queue, t_room *to_add, t_room *current);

/*
	Fonction pour la modification du graphe, la creation de chemin et la distribution.
*/

void		ft_clean(t_map *data, int **adj_mat);
void		ft_init_bfs(t_queue *bfs_queue, t_map *data);
void		ft_set_bfs(t_map *data);
int			**ft_bfs(t_map *data, int **adj_mat);
int			**ft_bhandari(t_map *data, int **adj_mat);
void		ft_distribution(int **tab_path, int nb_path, int nb_ants);
int			**ft_print(int **tab, t_map *data);

/*
	Fonction de gestion des leaks.
*/

void		ft_free_queue(t_queue queue, int len);
void		ft_free(t_map *data, int **tab_path);

/*
	Fonction de gestion du buffer.
*/

void		ft_write_in_buffer(t_buff *buff, char c, int len);
void		ft_putstr_buffer(t_buff *buff, char *str, int len);
void		ft_flush_buffer(t_buff *buff);

/*
	Fonction de Debug.
*/

void		print_info(t_map *data);
void		ft_debug_line_adj_mat(int *line, size_t size);
void		ft_debug_room(t_room *room);
void		ft_debug_rooms(t_room **rooms, size_t size);
void		ft_debug_queue(t_queue bfs_queue);
void		ft_debug_single_path(int *path, int len, t_map *data);
void		ft_debug_print(int **ants, t_map *data, int **tab);
void		ft_debug_collission(t_map *data, int **tab_path);
void		ft_debug_path(t_map *data, t_room *end_point, int **adj_mat);
#endif

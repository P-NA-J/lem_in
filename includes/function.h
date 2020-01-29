/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:51:52 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/28 10:26:56 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H

# define FUNCTION_H

typedef int	t_bool;

t_map		*parser(void);
t_preparse	*pre_parser(void);
t_bool		ft_parsing(t_list *data, t_map *galery);
uint32_t	jenkins_hash(char *name);
t_room		*get_next_room(t_preparse *prep, t_map *data);
t_room		**get_rooms(t_map *data, t_preparse *prep);
t_room		*parse_comment(t_preparse *prep, t_map *data);
int			get_pipes(t_map **data, t_preparse *prep);
t_map		*which_error(t_map *data, int type);
void		free_all(t_map *data);
char		*ft_passing_name(char *str);
t_bool		ft_is_comment(char *str, t_bool condition);
t_bool		ft_is_room(char *str);
t_bool		ft_is_tube(char *str);
t_bool		ft_is_numb_str(char **str);
char		*ft_strcsub(char *s, char c);
int			count_char_until(char *str, char c, char u);
void		print_info(t_map *data);
int			*ft_bfs(t_map *galery, int **adj_mat, t_room *start);
int			ft_line_check(int *line, int len);
int			ft_path_length_matrix(int **adj_mat, t_map *galery, int c_index);
void		ft_reset_matrix(t_map *galery);
int			*ft_get_aug_path(t_room *end_point, int **adj_mat);
void		ft_aug_clean(t_room **rooms, int len);
void		ft_set_bfs(t_map *galery);
int			*ft_path_builder(t_room *end_point, int **adj_mat);
t_room		*ft_remove_queue(t_queue *bfs_queue);
void		ft_add_queue(t_queue *bfs_queue, t_room *to_add, t_room *current, int time);
int			*ft_augmented_bfs(t_map *galery, int **adj_mat, t_room *start);
void		ft_debug_room(t_room *room, int mode);
void		ft_debug_rooms(t_room **rooms, size_t size, int mode);
void		ft_debug_queue(t_queue bfs_queue, int mode);
void		ft_debug_single_path(int *path, int len, t_map *galery);
int			**ft_mat_mirror_change(int **adj_mat, int value, int i_1, int i_2);
void		ft_distribution(int **tab_path, int nb_path, int nb_ants);
int			**ft_mult_bfs(t_map *galery, int **adj_mat);
void		ft_free(t_map *data, int **tab_path);
int			**ft_print(int **tab, t_map *data);
void		ft_free_queue(t_queue queue, int len);
void		ft_write_in_buffer(t_buff *buff, char c, int len);
void		ft_putstr_buffer(t_buff *buff, char *str, int len);
void		ft_flush_buffer(t_buff *buff);
void		ft_debug_print(int **ants, t_map *data, int **tab);
int			*ft_clean(t_map *data, int **adj_mat);
#endif

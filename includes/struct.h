/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:23:49 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 15:08:49 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# define BASE_MALLOC 8192

struct s_pipe;
struct s_room;

typedef struct			s_room
{
	char				*name;
	struct s_room		*prev;
	uint32_t			hash;
	int					index;
	int					features;
	int					path_occurence;
	int					time;
	int					coord_x;
	int					coord_y;
}						t_room;

typedef struct			s_preparse
{
	char				*buffer;
	char				*tmp_buff;
	long				size;
	int					reload;
	long				curr_index;
	struct s_room		hashed_rooms[PRIME];
	int					s_or_e;
	char				*r1;
	char				*r2;
	uint32_t			h_r1;
	uint32_t			h_r2;
}						t_preparse;

typedef struct			s_buff
{
	int					i;
	char				buff[BUFF_SIZE + 1];
}						t_buff;

typedef struct			s_map
{
	t_room				*start;
	t_room				*end;
	t_room				**rooms;
	t_preparse			*preparse;
	t_buff				buff;
	int					**adj_mat;
	int					nb_ants;
	int					nb_rooms;
	int					nb_path;
	int					is_augmented;
}						t_map;

typedef struct			s_queue
{
	t_room				*queue[PRIME];
	size_t				index;
}						t_queue;
#endif

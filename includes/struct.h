/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:23:49 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/02 21:39:17 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# define BASE_MALLOC 8192

struct 					s_pipe;
struct					s_room;

typedef struct			s_preparse
{
	char				*buffer;
	long				size;					
	int					reload;
	long				curr_index;
	struct s_room		*hashed_rooms[UINT_MAX];
}						t_preparse;

typedef struct			s_room
{
	char				*name;
	struct s_pipe		*pipes;
	int					features;
	// occupied
	// connected to End
	// marked
	int					coord_x;
	int					coord_y;
}						t_room;

typedef	struct			s_pipe
{
	t_room				connected[2];
	int					features;
	// cut or not
	// BFS return values
}						t_pipe;

typedef struct			s_path
{
	t_room				*from;
	t_room				*to;
	t_pipe				*connection;
}						t_path;

typedef struct			s_map
{
	t_room				*start;
	t_room				*end;
	t_room				**rooms;
	t_preparse			*preparse;
	int					nb_ants;
	int					nb_rooms;
}						t_map;


#endif

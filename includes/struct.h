/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:23:49 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/07 19:38:14 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# define BASE_MALLOC 8192

struct 					s_pipe;
struct					s_room;


typedef struct			s_room
{
	char				*name;
	struct s_pipe		*pipes;
	uint32_t			hash;
	int					index;
	struct s_room		*next;
	int					features;
	// occupied
	// connected to End
	// marked
	// Init_success
	// added to neighbors
	int					coord_x;
	int					coord_y;
}						t_room;

typedef struct			s_preparse
{
	char				*buffer;
	long				size;					
	int					reload;
	long				curr_index;
	struct s_room		hashed_rooms[PRIME];
	char				*r1;
	char				*r2;
	uint32_t			h_r1;
	uint32_t			h_r2;
}						t_preparse;

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
	t_room				**neighbors;
	t_preparse			*preparse;
	int					**adj_mat;
	int					nb_ants;
	int					nb_rooms;
	//int				error;
}						t_map;

// faire une structure pour gere les types d'erreurs

#endif

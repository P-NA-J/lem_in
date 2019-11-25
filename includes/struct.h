/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:23:49 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/25 19:08:15 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

//typedef struct s_room t_room;

typedef	struct	s_pipe
{
	struct s_room		connected[2];
	int			features;
	// cut or not
	// BFS return values
}				t_pipe;

typedef struct	s_room
{
	char		*name;
	t_pipe		*pipes;
	int			features;
	// occupied
	// connected to End
	// marked
}				t_room;

typedef struct	s_path
{
	t_room		*from;
	t_room		*to;
	t_pipe		*connection;
}				t_path;

typedef struct	s_map
{
	t_room		*start;
	t_room		*end;
	int			nb_ants;


#endif

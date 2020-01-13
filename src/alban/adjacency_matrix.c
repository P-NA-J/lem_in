/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:34:49 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/21 09:00:11 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int				get_adjacency_matrix(t_map *data)
{
	int		**adj_mat;
	int		curr_room;

	adj_mat = NULL;
	curr_room = 0;
	if (!(adj_mat = (int **)ft_memalloc(sizeof(int *) * data->nb_rooms)))
		return (FALSE);
	while (curr_room < data->nb_rooms)
	{
		if (!(adj_mat[curr_room] = (int *)ft_memalloc(sizeof(int) * data->nb_rooms)))
			return (FALSE);
		curr_room++;
	}
	data->adj_mat = adj_mat;
	return (TRUE);
}

int				get_hashes_rs(t_preparse *prep)
{
	if (!(prep->r1 = ft_strcsub(prep->buffer, '-')))
		return (FALSE);
	prep->buffer += ft_strlen(prep->r1) + 1;
	if (!(prep->r2 = ft_strcsub(prep->buffer, '\n')))
		return (FALSE);
	prep->buffer += ft_strlen(prep->r2) + 1;
	prep->h_r1 = jenkins_hash(prep->r1);
	prep->h_r2 = jenkins_hash(prep->r2);
	free(prep->r1);
	free(prep->r2);
	return (TRUE);
}

// add check for wrong input 
int				parse_pipes(t_map **data, t_preparse *prep)
{
	int curr_room1;
	int curr_room2;

	curr_room1 = 0;
	curr_room2 = 0;
	// add check for comments
	while (*prep->buffer)
	{
		while (*prep->buffer == '#')
			prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
		if (count_char_until(prep->buffer, '-', '\n') != 1)
			return (FALSE);
		if ((get_hashes_rs(prep)) == FALSE)
			return (FALSE);
		// add hash_check protection
		curr_room1 = prep->hashed_rooms[prep->h_r1].index;
		curr_room2 = prep->hashed_rooms[prep->h_r2].index;
		(*data)->adj_mat[curr_room1][curr_room2] = 1;
		(*data)->adj_mat[curr_room2][curr_room1] = 1;
	}
	return (TRUE);
}

int				get_pipes(t_map **data, t_preparse *prep)
{
	if (get_adjacency_matrix(*data) == FALSE)
		return (FALSE);
	if (parse_pipes(data, prep) == FALSE)
		return (FALSE);
	return (TRUE);
}


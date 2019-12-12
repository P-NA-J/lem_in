/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:34:49 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/09 16:59:52 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				get_adjacency_matrix(t_map *data)
{
	int		**adj_mat;
	int		curr_room;

	adj_mat = NULL;
	curr_room = 0;
	if (!(adj_mat = (int **)malloc(sizeof(int *) * data->nb_rooms)))
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

// add check for comments
// add check for wrong input 
// add hash_check protection
// add malloc protections
int				parse_pipes(t_map **data, t_preparse *prep)
{
	int curr_room1;
	int curr_room2;

	curr_room1 = 0;
	curr_room2 = 0;
	while (*prep->buffer)
	{
		if (count_char_until(prep->buffer, '-', '\n') != 1)
			return (FALSE);
		prep->r1 = ft_strcsub(prep->buffer, '-');
		prep->buffer += ft_strlen(prep->r1) + 1;
		prep->r2 = ft_strcsub(prep->buffer, '\n');
		prep->buffer += ft_strlen(prep->r2) + 1;
		prep->h_r1 = jenkins_hash(prep->r1);
		prep->h_r2 = jenkins_hash(prep->r2);
		curr_room1 = prep->hashed_rooms[prep->h_r1].index;
		curr_room2 = prep->hashed_rooms[prep->h_r2].index;
		(*data)->adj_mat[curr_room1][curr_room2] = 1;
		(*data)->adj_mat[curr_room2][curr_room1] = 1;
		free(prep->r1);
		free(prep->r2);
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

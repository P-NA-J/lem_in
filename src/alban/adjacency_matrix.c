/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:34:49 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/07 16:35:45 by aboitier         ###   ########.fr       */
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
		if (!(adj_mat[curr_room] = (int *)ft_memalloc(sizeof(int)
										* data->nb_rooms)))
			return (FALSE);
		curr_room++;
	}
	data->adj_mat = adj_mat;
	return (TRUE);
}



int				connect_rooms(t_map *data, t_preparse *prep)
{
	int curr_room1;
	int curr_room2;

	if (!(compare_names(prep->r1, &(prep->h_r1), prep))
	|| (!(compare_names(prep->r2, &(prep->h_r2), prep))))
	{
		free(prep->r1);
		free(prep->r2);
		return (FALSE);
	}
	curr_room1 = prep->hashed_rooms[prep->h_r1].index;
	curr_room2 = prep->hashed_rooms[prep->h_r2].index;
	set_links_tab(curr_room1, curr_room2, data);
	set_links_tab(curr_room2, curr_room1, data);
	data->adj_mat[curr_room1][curr_room2] = 1;
	data->adj_mat[curr_room2][curr_room1] = 1;
	free(prep->r1);
	free(prep->r2);
	return (TRUE);
}

int				parse_pipes(t_map **data, t_preparse *prep)
{
	int i;

	i = 0;
	while (*prep->buffer)
	{
		while (*prep->buffer == '#')
			prep->buffer += ft_strclen(prep->buffer, '\n') + 1;
		if (count_char_until(prep->buffer, '-', '\n') != 1)
			return (FALSE);
		if ((get_hashes_rs(prep)) == FALSE)
			return (FALSE);
		if (connect_rooms(*data, prep) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int				get_pipes(t_map **data, t_preparse *prep)
{
	if (get_adjacency_matrix(*data) == FALSE)
		return (FALSE);
	if (get_links_tab(*data) == FALSE)
		return (FALSE);
	if (parse_pipes(data, prep) == FALSE)
		return (FALSE);
	return (TRUE);
}

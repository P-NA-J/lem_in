/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:34:49 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/06 13:55:02 by aboitier         ###   ########.fr       */
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

int				get_hashes_rs(t_preparse *prep)
{
	if (!(prep->r1 = ft_strcsub(prep->buffer, '-')))
		return (FALSE);
	prep->buffer += ft_strlen(prep->r1) + 1;
	if (!(prep->r2 = ft_strcsub(prep->buffer, '\n')))
	{
		free(prep->r1);
		return (FALSE);
	}
	prep->buffer += ft_strlen(prep->r2) + 1;
	prep->h_r1 = jenkins_hash(prep->r1);
	prep->h_r2 = jenkins_hash(prep->r2);
	return (TRUE);
}

int				compare_names(char *to_connect,
				uint32_t *h_rx, t_preparse *prep)
{
	int diff;

	diff = 0;
	while (ft_strcmp(prep->hashed_rooms[*h_rx].name,
					to_connect) != 0 && diff++ < 10)
	{
		*h_rx = (*h_rx < PRIME - 1) ? *h_rx += 1 : 1;
		if (diff == 9)
			return (FALSE);
	}
	return (TRUE);
}

int				set_links_tab(int curr_room1, int curr_room2, t_map *data)
{
	int i;
	
	i = 0;
	while (data->links_tab[i + curr_room1 * LINK] != -1)
		i++;
	data->links_tab[i + curr_room1 * LINK] = curr_room2;
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

int				get_links_tab(t_map *data)
{
	int		*links_tab;
	long	i;
	long	size;

	i = 0;
	size = data->nb_rooms * LINK;
	if (!(links_tab = (int *)malloc(sizeof(int) * size)))
		return (FALSE);
	while (i < size)
	{
		links_tab[i] = - 1;	
		i += 1;
	}
	data->links_tab = links_tab;
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
	link_tabs(*data);
	return (TRUE);
}

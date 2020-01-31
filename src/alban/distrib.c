/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:02:13 by aboitier          #+#    #+#             */
/*   Updated: 2020/01/31 03:35:19 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	swp_rooms_tab(t_map *data, int ind_end, int ind_nb_rooms)
{		
	t_room 	*swap;
	
	swap = NULL;
	swap = data->rooms[ind_nb_rooms];
	data->rooms[ind_nb_rooms] = data->rooms[ind_end];
	data->rooms[ind_end] = swap;
	data->end = data->rooms[ind_nb_rooms];
}

void	swp_adj_mat(t_map *data, int ind_end, int ind_nb_rooms)
{
	int i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (i < data->nb_rooms)
	{
		tmp = data->adj_mat[i][ind_end];
		data->adj_mat[i][ind_end] = data->adj_mat[i][ind_nb_rooms];
		data->adj_mat[i][ind_nb_rooms] = tmp;

		tmp = data->adj_mat[ind_end][i];
		data->adj_mat[ind_end][i] = data->adj_mat[ind_nb_rooms][i];
		data->adj_mat[ind_nb_rooms][i] = tmp;
		i++;
	}
}

void	replace_end(t_map *data)
{
	int 	ind_end;
	int		ind_nb_rooms;

	ind_end = data->end->index;
	ind_nb_rooms = data->nb_rooms - 1;
	swp_adj_mat(data, ind_end, ind_nb_rooms);
	swp_rooms_tab(data, ind_end, ind_nb_rooms);
}

int		distrib(t_map *data)
{
	if (data->end->index != data->nb_rooms)
		replace_end(data);
//	send one ant per path;
		
//	earliest ant to get in
//		data->earliest
//	last ant to get in
//		data->latest
//	while (last ant to get in is inside != nb_ants)
//	printf("L-%ant_number-%roomname")
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:37:15 by aboitier          #+#    #+#             */
/*   Updated: 2020/01/31 19:20:01 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	swp_rooms_tab(t_map *data, int ind_s_or_e, int ind_nb_rooms, int choice)
{		
	t_room 	*swap;
	
	swap = NULL;
	if (choice == 1)
	{
		swap = data->rooms[0];
		data->rooms[0] = data->rooms[ind_s_or_e];
		data->rooms[ind_s_or_e] = swap;
		data->start = data->rooms[0];
	}
	else
	{
		swap = data->rooms[ind_nb_rooms];
		data->rooms[ind_nb_rooms] = data->rooms[ind_s_or_e];
		data->rooms[ind_s_or_e] = swap;
		data->end = data->rooms[ind_nb_rooms];
	}
}

void	replace_end(t_map *data)
{
	int 	ind_end;
	int		ind_nb_rooms;

	ind_end = data->end->index;
	ind_nb_rooms = data->nb_rooms - 1;
	swp_rooms_tab(data, ind_end, ind_nb_rooms, 2);
}

void	replace_start(t_map *data)
{
	int		ind_start;

	ind_start = data->start->index;
	swp_rooms_tab(data, ind_start, 0, 1);
}

void	replace_sink_tank(t_map *data)
{
	if (data->start->index != data->rooms[0]->index)
		replace_start(data);
	if (data->end->index != data->nb_rooms)
		replace_end(data);
}



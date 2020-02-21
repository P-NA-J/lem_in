/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:44:12 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/21 13:31:02 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int				set_links_tab(int curr_room1, int curr_room2, t_map *data)
{
	int i;

	i = 0;
	while (data->links_tab[i + curr_room1 * LINK] != -1)
		i++;
	data->links_tab[i + curr_room1 * LINK] = curr_room2;
	data->rooms[curr_room1]->nb_link++;
	return (TRUE);
}

int				get_links_tab(t_map *data)
{
	long	i;
	long	size;

	i = 0;
	size = data->nb_rooms * LINK;
	if (!(data->links_tab = (int *)malloc(sizeof(int) * size)))
		return (FALSE);
	while (i < size)
	{
		if (i % LINK == 0)
			data->rooms[i / LINK]->link = data->links_tab + i;
		data->links_tab[i] = -1;
		i += 1;
	}
	return (TRUE);
}

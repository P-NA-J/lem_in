/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 17:10:23 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/10 17:11:30 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>

t_room			**malloc_neighbors(t_map *data)
{
	t_room		**neighbors;

	neighbors = NULL;
	if (!(neighbors = (t_room **)ft_memalloc(sizeof(t_room *) * data->nb_rooms)))
		return (NULL);
	return (neighbors);
}

int				add_neighbor(t_room *father, t_room *child)
{
	t_room	*tmp_father;	
	t_room	*tmp_child;	

	tmp_father = father;
	tmp_child = child;

	tmp_child->next = NULL;


	while (tmp_father->next != NULL)
		tmp_father = tmp_father->next;
	tmp_father->next = child;
	return (TRUE);
}

t_room			**get_neighbors(t_map *data)
{
	int 	x;
	int		empty;
	t_room	**neighbors;

	if (!(neighbors = malloc_neighbors(data)))
		return (NULL);
	empty = 0;
	x = 0;
	data->rooms[0]->features |= ADDED_NEIGHBORS;
	neighbors[0] = data->rooms[0];
	while (x < data->nb_rooms)
	{
		if (data->adj_mat[0][x] == 1)
		{	
			while (neighbors[empty] != NULL)
				empty++;	
			data->rooms[x]->features |= ADDED_NEIGHBORS;
			neighbors[empty] = data->rooms[x];
	//		add_neighbor(neighbors[0], data->rooms[x]);
		}
		x++;
	}
	int curr_room = 1;
	int index;
	while (curr_room < data->nb_rooms)
	{	 
		index = neighbors[curr_room]->index;	
		x = 0;
		while (x < data->nb_rooms)
		{
			if (data->adj_mat[index][x] == 1) 
			{
				if ((data->rooms[x]->features & ADDED_NEIGHBORS) == FALSE)
				{
					while (neighbors[empty] != NULL)
						empty++;
					data->rooms[x]->features |= ADDED_NEIGHBORS;
					neighbors[empty] = data->rooms[x];
				}

//				add_neighbor(neighbors[index], data->rooms[x]);

			}
			x++;
		}
		curr_room++;
	}

	return (neighbors);

}

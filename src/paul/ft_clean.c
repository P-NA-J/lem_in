/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:59:33 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:24:02 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Reposisionne les liens après la suppression d'un lien.
*/

void	ft_slide_link(int *link, int index)
{
	while (link[index] >= 0)
	{
		link[index] = link[index + 1];
		index += 1;
	}
}

/*
**	Supprime un lien et repositionne correctement les
**	autres liens de la salle en cours.
*/

void	ft_remove_link(int curr_i, t_room *current)
{
	int	index;

	index = 0;
	while (current->link[index] != curr_i)
	{
		index += 1;
	}
	ft_slide_link(current->link, index);
	current->nb_link -= 1;
}

/*
**	Pour une salle donnée, on analyse ses liens pour avancer
**	dans le graphe et effacer les liens isolés.
*/

void	ft_adj_mat_line_clean_process(t_map *data, int **adj_mat,
										t_queue *c_queue, t_room *current)
{
	int		i;
	t_room	*room;

	if (current->features != IS_START && current->features != IS_END
		&& current->nb_link == 1)
	{
		room = data->rooms[current->link[0]];
		room->features = UNQUEUE;
		ft_add_front_queue(c_queue, room, room->prev);
		adj_mat = ft_mat_mirror_change(adj_mat, NO_LINK,
										current->index, room->index);
		ft_remove_link(current->index, room);
		return ;
	}
	i = 0;
	while (i < current->nb_link)
	{
		room = data->rooms[current->link[i]];
		if (room->features == UNQUEUE
			&& room->features != IS_END)
			ft_add_queue(c_queue, room, current, 0);
		i += 1;
	}
}

/*
**	Fonction qui efface les culs de sac en la parcourant avec un bfs.
*/

void	ft_clean(t_map *data, int **adj_mat)
{
	t_queue	c_queue;
	t_room	*current;

	data->start->features = IS_START;
	data->end->features = IS_END;
	c_queue.queue[0] = data->start;
	c_queue.index = 1;
	while (c_queue.index != 0)
	{
		current = ft_remove_queue(&c_queue);
		ft_adj_mat_line_clean_process(data, adj_mat, &c_queue, current);
		current->features = VISITED;
	}
}

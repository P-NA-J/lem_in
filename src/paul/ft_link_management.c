/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:13:58 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 19:28:57 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Gestion d'un lien orienté / appartenant à un chemin augmentant.
*/

int		ft_augmented_link_management(t_map *data)
{
	if (data->decision > 1)
		data->decision -= 1;
	else if (data->decision == 1)
		return (TRUE);
	return (FALSE);
}

/*
**	Process d'actualisation / ajout d'une salle
**	lorsqu'on entre sur  un chemin augmentant.
*/

void	ft_unchanged_link_process(t_queue *bfs_q, t_room *i_room,
									t_room *current, t_room *aug_room)
{
	if (i_room->time > current->time || (i_room->features == UNQUEUE &&
		aug_room->features == UNQUEUE))
	{
		ft_actualisation(i_room, current, 1);
		i_room->features = QUEUE;
		ft_add_queue(bfs_q, aug_room, i_room, -1);
	}
}

/*
**	Gestion d'un lien non orienté.
*/

void	ft_unchanged_link_management(int index, t_room *current,
									t_map *data, t_queue *bfs_q)
{
	int	tmp_aug;

	tmp_aug = 0;
	if (ft_line_check(data->rooms[index], data->adj_mat[index]) == IGNORE)
		ft_add_queue(bfs_q, data->rooms[index], current, 1);
	else if (((tmp_aug = ft_check_line(data->rooms[index],
				data->adj_mat[index], AUGMENTED)) != IGNORE)
					&& data->decision == 1)
		ft_unchanged_link_process(bfs_q, data->rooms[index],
									current, data->rooms[tmp_aug]);
}

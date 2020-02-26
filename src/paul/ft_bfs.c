/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:46:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/21 17:44:50 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
**	Cette fonction verifie que l'on peut interagir vec la salle :
**	soit l'ajouter, soit l'actualiser.
*/

int		ft_actionnable(t_map *data, int **adj_mat, int index, int curr)
{
	if (ft_check_line(data->rooms[curr], adj_mat[index], INFINY) != IGNORE)
		return (FALSE);
	else if (data->rooms[index]->features == UNQUEUE)
		return (TRUE);
	else if (data->rooms[index]->time > data->rooms[curr]->time
			&& index != data->rooms[curr]->prev->index)
		return (TRUE);
	return (FALSE);
}

/*
**	Calcul le nombre de salle qui peuvent être ajoutée ou actualisée.
*/

int		ft_occurence_count(t_map *data, int **adj_mat,
							t_room *current, int len)
{
	int			i;
	int			count;

	count = 0;
	i = 0;
	while (i < len)
	{
		if (ft_actionnable(data, adj_mat, current->link[i],
							current->index) == TRUE)
			count += 1;
		i += 1;
	}
	return (count);
}

/*
**	Gestion des liens pour une salle donnée.
*/

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q, t_room *current)
{
	int			i;
	int			*line;
	int			link;

	if (adj_mat[current->index][data->end->index] == UNCHANGED)
		return (ft_add_front_queue(bfs_q, data->end, current));
	data->decision = ft_occurence_count(data, adj_mat, current,
										current->nb_link);
	line = adj_mat[current->index];
	i = 0;
	while (i < current->nb_link)
	{
		link = current->link[i];
		if (line[link] == AUGMENTED)
		{
			if (ft_augmented_link_management(data) == TRUE)
				ft_add_queue(bfs_q, data->rooms[link], current, -1);
		}
		else if (line[link] == UNCHANGED)
			ft_unchanged_link_management(link, current, data, bfs_q);
		i += 1;
	}
}

/*
**	Parcours du graphe a la recherche d'un chemin vers end.
**	Boucle tant qu'il reste des salles non explorées dans la queue.
**	Ne fais que depop la salle du dessus de la queue.
*/

int		**ft_bfs(t_map *data, int **adj_mat)
{
	t_queue	bfs_queue;
	t_room	*current;

	ft_init_bfs(&bfs_queue, data);
	while (bfs_queue.index != 0)
	{
		if ((current = ft_remove_queue(&bfs_queue)) == data->end)
		{
			data->opti.index = current->prev->index;
			return (adj_mat);
		}
		ft_adj_mat_line_process(data, adj_mat, &bfs_queue, current);
	}
	return (NULL);
}

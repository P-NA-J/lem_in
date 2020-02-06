/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/06 18:53:47 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Cette fonction verifie que l'on peut interagir vec la salle :
	soit l'ajouter, soit l'actualiser.
*/

int	ft_actionnable(t_map *data, int **adj_mat, int index, int curr)
{
	if (ft_check_line(adj_mat[index], data->nb_rooms, INFINY) != IGNORE)
		return (FALSE);
	else if (data->rooms[index]->features == UNQUEUE)
		return (TRUE);
	else if (data->rooms[index]->time > data->rooms[curr]->time && index != data->rooms[curr]->prev->index)
		return (TRUE);
	return (FALSE);
}

/*
	Calcul le nombre de salle qui peuvent être ajoutée ou actualisée.
*/

int	ft_occurence_count(t_map *data, int **adj_mat, int curr_i, int len)
{
	int i;
	int	count;

	count = 0;
	i = 0;
	while (i < len)
	{
		if (adj_mat[curr_i][i] != NO_LINK)
			if (ft_actionnable(data, data->adj_mat, i, curr_i) == TRUE)
				count += 1;
		i += 1;
	}
	return (count);
}

/*
	Parcours tout les liens d'une salle et appelle la fonction de gestion du tube en fonction de son état.
	S'assure d'abord que la salle n'est pas connecté à end, sinon on force l'arret du bfs.
*/

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	i;
	int	tmp_aug;
	int	decision;

	decision = ft_occurence_count(data, adj_mat, current->index, data->nb_rooms);
	i = 0;
	if (adj_mat[current->index][data->end->index] == UNCHANGED)
		return(ft_add_front_queue(bfs_q_ref, data->end, current));
	while (i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == NO_LINK || adj_mat[current->index][i] == BLOCKED)
			;
		else if (adj_mat[current->index][i] == AUGMENTED && decision > 1)
			decision -= 1;
		else if (adj_mat[current->index][i] == AUGMENTED && decision == 1)
			ft_add_queue(bfs_q_ref, data->rooms[i], current, -1);
		else if (adj_mat[current->index][i] == UNCHANGED && ft_line_check(adj_mat[i], data->nb_rooms) == IGNORE)
			ft_add_queue(bfs_q_ref, data->rooms[i], current, 1);
		else if (adj_mat[current->index][i] == UNCHANGED && (tmp_aug = ft_check_line(adj_mat[i], data->nb_rooms, AUGMENTED) != IGNORE) && decision == 1)
		{
			if (data->rooms[i]->time > current->time || (data->rooms[i]->features == UNQUEUE && data->rooms[tmp_aug]->features == UNQUEUE))
			{
				ft_actualisation(data->rooms[i], current, 1);
				data->rooms[i]->features = QUEUE;
				ft_add_queue(bfs_q_ref, data->rooms[tmp_aug], data->rooms[i], -1);
			}
		}
		i += 1;
	}
}


/* 
	Parcours du graphe a la recherche d'un chemin vers end.
	Boucle tant qu'il reste des salles non explorées dans la queue.
	Ne fais que depop la salle du dessus de la queue.
*/

int	**ft_bfs(t_map *data, int **adj_mat)
{
	t_queue	bfs_queue;
	t_room	*current;

	ft_init_bfs(&bfs_queue, data);
	while (bfs_queue.index != 0)
	{
		if ((current = ft_remove_queue(&bfs_queue)) == data->end)
			return (adj_mat);
		ft_debug_room(current);
		ft_adj_mat_line_process(data, adj_mat, &bfs_queue, current);
	}
	return (NULL);
}

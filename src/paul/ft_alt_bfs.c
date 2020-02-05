/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alt_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:40:47 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/05 16:54:54 by pauljull         ###   ########.fr       */
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
	Gestion d'un lien orienté / appartenant à un chemin augmentant.
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
	Process d'actualisation / ajout d'une salle lorsqu'on entre sur  un chemin augmentant.
*/

void	ft_unchanged_link_process(t_queue *bfs_q, t_room *i_room, t_room *current, t_room *aug_room)
{
	if (i_room->time > current->time || (i_room->features == UNQUEUE && aug_room->features == UNQUEUE))
	{
		ft_actualisation(i_room, current, 1);
		i_room->features = QUEUE;
		ft_add_queue(bfs_q, aug_room, i_room, -1);
	}
}

/*
	Gestion d'un lien non orienté.
*/

void	ft_unchanged_link_management(int index, t_room *current, t_map *data, t_queue *bfs_q)
{
	int	tmp_aug;
	int	tmp_clean;

	if ((tmp_clean = ft_line_check(current, data->adj_mat[index])) == IGNORE)
		ft_add_queue(bfs_q, data->rooms[current->link[index]], current, 1);
	else if ((tmp_aug = ft_check_line(current, data->adj_mat[index], AUGMENTED) != IGNORE) && data->decision == 1)
		ft_unchanged_link_process(bfs_q, data->rooms[current->link[index]], current, data->rooms[tmp_aug]);
}

/*
	Gestion des liens pur une salle donnée.
*/

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q, t_room *current)
{
	int	i;
	int	tmp;
	int *line;
	int link;

	if (adj_mat[current->index][data->end->index] == UNCHANGED)
		return(ft_add_front_queue(bfs_q, data->end, current));
	data->decision = ft_occurence_count(data, adj_mat, current->index, data->nb_rooms);
	line = adj_mat[current->index];
	i = 0;
	while (i < current->nb_link)
	{
		link = current->link[i];
		if (line[link] == AUGMENTED)
			if (ft_augmented_link_management(data) == TRUE)
				ft_add_queue(bfs_q, data->rooms[link], current, -1);
		else if (line[link] == UNCHANGED)
			ft_unchanged_link_management(link, current, data, bfs_q);
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
		ft_adj_mat_line_process(data, adj_mat, &bfs_queue, current);
	}
	return (NULL);
}
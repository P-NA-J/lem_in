/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 10:18:23 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 15:53:59 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Calcul le nombre de salle qui ne sont pas queue et possiblement empruntable pour une salle donnée.
*/

int		ft_occurence_count(t_map *data, int *tab, int to_find, int len)
{
	int i;
	int	occurence;

	i = -1;
	occurence = 0;
	while (++i < len)
	{
		if (tab[i] == to_find && data->rooms[i]->features != QUEUE)
			occurence += 1;
	}
	return (occurence);
}

/*
	Fonction de gestion des tubes orienté.
*/

void	ft_augmented_link_management(t_map *data, int index,
							t_queue *bfs_q_ref, t_room *current)
{
	int	nb_branch;

	nb_branch = ft_occurence_count(data, data->adj_mat[current->index], 1, data->nb_rooms);
	if (nb_branch == 1)
		ft_add_queue(bfs_q_ref, data->rooms[index], current, -1);
}

/*
	Fonction de gestion des tubes non orientés.
	nb_branch = le nombre de salle relié qui n'ont pas déjà été ajoutée.
	tmp_inf = index de la salle qui a un lien remontant vers START, -1 si il n'y en a pas.
	tmp_aug = index de la salle qui a un lien remontant vers une autre salle que START, -1 si il n'y en a pas.
*/

void	ft_unchanged_link_management(t_map *data, int index,
							t_queue *bfs_q_ref, t_room *current)
{
	int	tmp_inf;
	int	tmp_aug;
	int	nb_branch;

	nb_branch = ft_occurence_count(data, data->adj_mat[current->index], UNCHANGED, data->nb_rooms);
	tmp_inf = ft_check_line(data->adj_mat[index], data->nb_rooms, INFINY);
	tmp_aug = ft_check_line(data->adj_mat[index], data->nb_rooms, AUGMENTED);
	if (tmp_inf != IGNORE)
		return ;
	else if (tmp_aug == IGNORE)
		ft_add_queue(bfs_q_ref, data->rooms[index], current, 1);
	else if (tmp_aug != IGNORE && nb_branch == 1)
	{
		if (data->rooms[index]->time > (current->time + 1))
		{
			data->rooms[index]->time = current->time + 1;
			data->rooms[index]->prev = current;
			ft_add_queue(bfs_q_ref, data->rooms[tmp_aug], data->rooms[index], -1);
		}
	}
}

/*
	Parcours tout les liens d'une salle et appelle la fonction de gestion du tube en fonction de son état.
	S'assure d'abord que la salle n'est pas connecté à end, sinon on force l'arret du bfs.
*/

void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	i;

	i = -1;
	if (adj_mat[current->index][data->end->index] == UNCHANGED)
	{
		ft_add_front_queue(bfs_q_ref, data->end, current);
		return ;
	}
	while (++i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == UNCHANGED)
			ft_unchanged_link_management(data, i, bfs_q_ref, current);
		else if (adj_mat[current->index][i] == AUGMENTED)
			ft_augmented_link_management(data, i, bfs_q_ref, current);
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

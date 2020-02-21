/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 09:03:20 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/21 09:56:21 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Fonction qui free une room.
*/

void	ft_free_room(t_room *room)
{
	free(room->name);
	free(room);
}

/*
	Fonction qui free le tableau de room.
*/

void	ft_free_room_tab(t_room **rooms, int nb_room)
{
	int	i;

	i = 0;
	while (i < nb_room)
		ft_free_room(rooms[i++]);
	free(rooms);
}

/*
	Fonction qui free la matrice d'adjacence.
*/

void	ft_free_adj_mat(int **adj_mat, int nb_path)
{
	int	i;

	i = 0;
	while (i < nb_path)
		free(adj_mat[i++]);
	free(adj_mat);
}

/*
	Fonction qui free la matrice d'adjacence et les différentes room.
*/

void	ft_free_all(t_map *data)
{
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	ft_free_room_tab(data->rooms, nb_rooms);
	ft_free_adj_mat(data->adj_mat, nb_rooms);
	free(data->links_tab);
	free(data->preparse->tmp_buff);
}
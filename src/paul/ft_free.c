/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 12:04:57 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/08 16:22:49 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_free_queue(t_queue queue, int len)
{
	ft_bzero(&queue, len);
	free(queue.queue);
}

void	ft_free_preparse(t_preparse *preparse)
{
	ft_bzero(preparse, sizeof(*preparse));
	free(preparse->buffer);
	free(preparse->tmp_buff);
	free(preparse->r1);
	free(preparse->r2);
	free(preparse);
}

void	ft_free_adj_mat(int **adj_mat, int nb_rooms)
{
	int	i;

	i = 0;
	while (i < nb_rooms)
	{
		ft_bzero(adj_mat[i], sizeof(int) * nb_rooms);
		free(adj_mat[i]);
		i += 1;
	}
	free(adj_mat);
}

void	ft_free_path_tab(int **tab, int nb_rooms)
{
	int	i;

	i = 0;
	while (i < nb_rooms)
	{
		ft_bzero(tab[i], sizeof(int) * (tab[i][0] + 2));
		free(tab[i]);
		i += 1;
	}
	free(tab);
}

void	ft_free_room(t_room *room)
{
	ft_bzero(room, sizeof(*room));
	free(room->name);
}

void	ft_free_rooms(t_room **rooms, int nb_room)
{
	int	i;

	i = 0;
	while (i < nb_room)
	{
		ft_bzero(rooms[i], sizeof(rooms[0][i]));
		free(rooms[i]->name);
		i += 1;
	}
	free(rooms);
}

void	ft_free(t_map *data, int **tab_path)
{
	ft_free_rooms(data->rooms, data->nb_rooms);
	ft_free_preparse(data->preparse);
	ft_free_path_tab(tab_path, data->nb_path);
	ft_free_adj_mat(data->adj_mat, data->nb_rooms);
	ft_bzero(data, sizeof(*data));
	free(data);
}

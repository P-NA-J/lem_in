/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:53:52 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/05 18:52:16 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdio.h>

void	ft_bubble_sort(int *tab, int len)
{
	int i;
	int j;
	int	i_min;
	int	min;

	i_min = 0;
	i = 0;
	while (i < len)
	{
		min = tab[i];
		i_min = i;
		j = i + 1;
		while (j < len)
		{
			if (tab[j] < min)
			{
				min = tab[j];
				i_min = j;
			}
			j += 1;
		}
		tab[i_min] = tab[i];
		tab[i] = min;
		i += 1;
	}
}

int		ft_check_raw(t_map *data, int **adj_mat, int index)
{
	int	i;
	int	count;

	if (index == data->end->index || index == data->start->index)
		return (FALSE);
	i = -1;
	count = 0;
	while (++i < data->nb_rooms)
	{
		if (adj_mat[i][index] != 0)
			count += 1;
	}
	if (count > 1)
		return (TRUE);
	return (FALSE);
}

void	ft_debug_collission(t_map *data)
{
	int	index;
	int count;

	count = 0;
	index = -1;
	while (++index < data->nb_rooms)
	{
		if (ft_check_raw(data, data->adj_mat, index) == TRUE)
		{
			printf(_RED "/!\\ ERROR COLLISION /!\\\n" _RESET);
			count += 1;
		}
	}
	if (count == 0)
		printf(_GREEN "/!\\ SUCCESS : NO COLLISION /!\\\n" _RESET);
}

void	ft_debug_print(int **ants, t_map *data, int **tab)
{
	int	i;
	int j;

	i = 0;
	while (i < data->nb_ants)
	{
		printf("ANTS Num %d | Position = %d\n", i + 1, ants[i][2]);
		i += 1;
	}
	printf("\n");
	i = 0;
	while (i < data->nb_path)
	{
		printf("PATH NUM %d | NB_FOURMI RESTANTES = %d\n", i + 1, tab[i][1]);
		j = 2;
		while (j < tab[i][0] + 2)
		{
			printf("ROOM = %s | ", data->rooms[tab[i][j]]->name);
			if (data->rooms[tab[i][j]]->features == OCCUPIED)
				printf("OCCUPIED");
			else
				printf("EMPTY");
			printf("\n");
			j += 1;
		}
		printf("\n");
		i += 1;
	}
}

void	ft_print_line(char c, size_t n)
{
	size_t i;

	i = 0;
	while (i++ < n)
	{
		printf(" ");
		fflush(stdout);
	}
	printf("%c\n", c);
}

void	ft_print_char_line(char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		printf("%c", c);
		fflush(stdout);
	}
	printf("\n");
}

void	ft_debug_room(t_room *room)
{
	size_t ret;

	ret = printf("[[ NAME ]]     ==> [[ " _GREEN " %s " _RESET "]]\n", room->name);
	ret = printf("[[ TIME ]]     ==> [[ " _GREEN " %d " _RESET "]]\n", room->time);
	ret = printf("[[ INDEX ]]    ==> [[ " _GREEN " %d " _RESET "]]\n", room->index);
	if (room->features == UNQUEUE)
		printf("[[ FEATURES ]]   ==> [[ " _GREEN " UNQUEUE " _RESET "]]\n");
	else if (room->features == QUEUE)
		printf("[[ FEATURES ]]   ==> [[ " _GREEN " QUEUE " _RESET "]]\n");
	else if (room->features == IS_START)
		printf("[[ FEATURES ]]   ==> [[ " _GREEN " IS_START " _RESET "]]\n");
	else if (room->features == IS_END)
		printf("[[ FEATURES ]]   ==> [[ " _GREEN " IS_END " _RESET "]]\n");
	else if (room->features == PATHED)
		printf("[[ FEATURES ]]   ==> [[ " _GREEN " PATHED " _RESET "]]\n");
	ret = printf("[[ ADDR ]]     ==> [[ " _GREEN " %p " _RESET "]]\n", room);
	if (room->prev != NULL)
	{
		ret = printf("\t[[ NAME ]]     ==> [[ " _YELLOW " %s " _RESET "]]\n", room->prev->name);
		ret = printf("\t[[ INDEX ]]    ==> [[ " _YELLOW " %d " _RESET "]]\n", room->prev->index);
		ret = printf("\t[[ TIME ]]     ==> [[ " _GREEN " %d " _RESET "]]\n", room->prev->time);
		ret = printf("\t");
		ret = printf("\t[[ ADDR ]]     ==> [[ " _YELLOW " %p " _RESET "]]\n", room->prev);
	}
	else
		ret = printf("\t[[ PREV ]] ==> [[ " _RED " NULL " _RESET "]]\n");
	printf("\n");
}

size_t	ft_max_len(t_room **rooms, size_t size)
{
	size_t max;
	size_t len;
	size_t i;

	i = 0;
	max = 0;
	while (i < size)
	{
		len = ft_strlen(rooms[i++]->name);
		if (max < len)
			max = len;
	}
	return (max);
}

void	ft_debug_rooms(t_room **rooms, size_t size)
{
	size_t	i;
	size_t cadre;

	i = 0;
	cadre = 37 + ft_max_len(rooms, size);
	ft_print_char_line('_', cadre);
	while (i < size)
		ft_debug_room(rooms[i++]);
	ft_print_char_line('_', cadre);
}

void	ft_debug_queue(t_queue bfs_queue)
{
	ft_debug_rooms(bfs_queue.queue, bfs_queue.index);
	printf("[[ INDEX ]] ==> %zu\n", bfs_queue.index);
}

void	ft_debug_line_adj_mat(int *line, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("[ %d ]", line[i++]);
		fflush(stdout);
	}
	printf("\n");
}

void	ft_debug_adj_mat(int **adj_mat, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size)
		ft_debug_line_adj_mat(adj_mat[i++], size);
}

void	ft_debug_single_path(int path[500], int len, t_map *data)
{
	int	i;

	i = 2;
	printf("[%d] ", path[0]);
	fflush(stdout);
	printf("[%d] ", path[1]);
	fflush(stdout);
	while (i <= len + 1)
	{
		printf("[%s]", data->rooms[path[i++]]->name);
		fflush(stdout);
	}
	printf("\n");
}

void	ft_print_path(t_map *data, int **adj_mat, int index, int nb_rooms)
{
	printf("[%d] [%s]\n", adj_mat[data->start->index][index], data->start->name);
	fflush(stdout);
	(void)nb_rooms;
/*	while (index != data->end->index)
	{
		printf("[%s]", data->rooms[index]->name);
		fflush(stdout);
		index = ft_go_to_next(adj_mat[index], nb_rooms);
	}
	printf("[%s]", data->rooms[index]->name);
		fflush(stdout);
	printf("\n");
*/}

void	ft_debug_path(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_rooms;
	int	nb_path;
	int	sum_path;
	int res_tmp;
	int res;

	res = -1;
	ft_bubble_sort(adj_mat[data->start->index], data->nb_rooms);
	nb_rooms = data->nb_rooms;
	i = -1;
	nb_path = 0;
	sum_path = 0;
	printf("nb_ants = %d\n", data->nb_ants);
	while (++i < nb_rooms)
	{
		if (adj_mat[data->start->index][i] != NO_LINK)
		{
			nb_path += 1;
			sum_path += adj_mat[data->start->index][i];
			res_tmp = (data->nb_ants + sum_path - nb_path) / nb_path;
			printf("[%d]\n", res_tmp);
			if (res == -1)
				res = res_tmp;
			if (res_tmp < res)
				res = res_tmp;
//			ft_print_path(data, adj_mat, i, nb_rooms);
		}
	}
	printf("\nNombre de tour [%d]\n", res);
}

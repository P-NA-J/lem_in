/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:53:52 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 08:24:59 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

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

void	ft_print_features(int features)
{
	size_t ret;

	if (features == IS_START)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " IS_START " _RESET "]]\n");
	else if (features == VISITED)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " VISITED " _RESET "]]\n");
	else if (features == UNQUEUE)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " UNQUEUE " _RESET "]]\n");
	else if (features == IS_END)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " IS_END " _RESET "]]\n");
	else if (features == AUG_START)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " AUG_START " _RESET "]]\n");
	else if (features == AUG_VISITED)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " AUG_VISITED " _RESET "]]\n");
	else if (features == INF)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " INF " _RESET "]]\n");
	else if (features == BLOCKED)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " BLOCKED " _RESET "]]\n");
	else if (features == QUEUE)
		printf("[[ FEATURES ]] ==> [[ " _GREEN " QUEUE " _RESET "]]\n");
}

void	ft_debug_room(t_room *room, int mode)
{
	size_t ret;

	ret = printf("[[ NAME ]]     ==> [[ " _GREEN " %s " _RESET "]]\n", room->name);
	ret = printf("[[ INDEX ]]    ==> [[ " _GREEN " %d " _RESET "]]\n", room->index);
	ft_print_features(room->features);
	ret = printf("[[ ADDR ]]     ==> [[ " _GREEN " %p " _RESET "]]\n", room);
	if (mode == FULL)
	{
		ret = printf("[[ HASH ]]     ==> [[ " _GREEN " %u " _RESET "]]\n", room->hash);
		ret = printf("[[ COORD_X ]]  ==> [[ " _GREEN " %d " _RESET "]]\n", room->coord_x);
		ret = printf("[[ COORD_Y ]]  ==> [[ " _GREEN " %d " _RESET "]]\n", room->coord_y);
	}
	if (room->prev != NULL)
	{
		ret = printf("\t[[ NAME ]]     ==> [[ " _YELLOW " %s " _RESET "]]\n", room->prev->name);
		ret = printf("\t[[ INDEX ]]    ==> [[ " _YELLOW " %d " _RESET "]]\n", room->prev->index);
		ret = printf("\t");
		ft_print_features(room->prev->features);
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

void	ft_debug_rooms(t_room **rooms, size_t size, int mode)
{
	size_t	i;
	size_t cadre;

	i = 0;
	cadre = 37 + ft_max_len(rooms, size);
	ft_print_char_line('_', cadre);
	while (i < size)
		ft_debug_room(rooms[i++], mode);
	ft_print_char_line('_', cadre);
}

void	ft_debug_queue(t_queue bfs_queue, int mode)
{
	ft_debug_rooms(bfs_queue.queue, bfs_queue.index, mode);
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

void	ft_debug_galery(t_map *galery)
{
	printf("[[ START ]]    ==> %s\n", galery->start->name);
	printf("[[ END ]]      ==> %s\n", galery->end->name);
	printf("[[ NB_ANTS ]]  ==> %d\n", galery->nb_ants);
	printf("[[ NB_ROOMS ]] ==> %d\n", galery->nb_rooms);
	ft_debug_rooms(galery->rooms, galery->nb_rooms, RESTRICT);
	ft_debug_adj_mat(galery->adj_mat, galery->nb_rooms);
}

void	ft_debug_single_path(int *path, int len, t_map *galery)
{
	int	i;

	i = 1;
	printf("[%d] ", path[0]);
	fflush(stdout);
	while (i <= len)
	{
		printf("[%s]", galery->rooms[path[i++]]->name);
		fflush(stdout);
	}
	printf("\n");
}
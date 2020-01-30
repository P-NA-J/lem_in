/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:53:52 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/30 16:55:33 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"
#include <stdio.h>

void	ft_debug_collission(t_map *data, int **tab_path)
{
	int i,j ,k, l, count;

	i = data->nb_path - 1;
	j = 0;
	k = 0;
	l = 0;
	count = 0;
	while (i > 0)
	{
		j = 3;
		while (j < tab_path[i][0] + 2)
		{
			k = i - 1;
			while (k >= 0)
			{
				l = 3;
				while (l < tab_path[k][0] + 2)
				{
					if (tab_path[i][j] == tab_path[k][l] && tab_path[i][j] != data->end->index)
					{
						count += 1;
						printf("/!\\ ERROR COLLISION /!\\\ntab_path[%d][%d] = %d tab_path[%d][%d] = %d\n", i, j, tab_path[i][j], k, l, tab_path[k][l]);
					}
					l += 1;
				}
				k -= 1;
			}
			j += 1;
		}
		i -= 1;
	}
	if (count == 0)
		printf("PAS DE COLLISION TOUT VA BIEN\n");
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
	else if (features == INFINY)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " INFINY " _RESET "]]\n");
	else if (features == BLOCKED)
		ret = printf("[[ FEATURES ]] ==> [[ " _GREEN " BLOCKED " _RESET "]]\n");
	else if (features == QUEUE)
		printf("[[ FEATURES ]] ==> [[ " _GREEN " QUEUE " _RESET "]]\n");
	else if (features == EMPTY)
		printf("[[ FEATURES ]] ==> [[ " _GREEN " EMPTY " _RESET "]]\n");
	else if (features == OCCUPIED)
		printf("[[ FEATURES ]] ==> [[ " _GREEN " OCCUPIED " _RESET "]]\n");
}

void	ft_debug_room(t_room *room)
{
	size_t ret;

	ret = printf("[[ NAME ]]     ==> [[ " _GREEN " %s " _RESET "]]\n", room->name);
	ret = printf("[[ TIME ]]     ==> [[ " _GREEN " %d " _RESET "]]\n", room->time);
	ret = printf("[[ INDEX ]]    ==> [[ " _GREEN " %d " _RESET "]]\n", room->index);
	ft_print_features(room->features);
	ret = printf("[[ ADDR ]]     ==> [[ " _GREEN " %p " _RESET "]]\n", room);
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

void	ft_debug_data(t_map *data)
{
	printf("[[ START ]]    ==> %s\n", data->start->name);
	printf("[[ END ]]      ==> %s\n", data->end->name);
	printf("[[ NB_ANTS ]]  ==> %d\n", data->nb_ants);
	printf("[[ NB_ROOMS ]] ==> %d\n", data->nb_rooms);
	ft_debug_rooms(data->rooms, data->nb_rooms);
	ft_debug_adj_mat(data->adj_mat, data->nb_rooms);
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

void	ft_debug_tab_path(t_room **rooms, int **tab_path, int n)
{
	int	i;
	int j;

	i = 0;
	while (i < n)
	{
		j = 1;
		while (j <= tab_path[i][0])
		{
			printf("[%s]", rooms[tab_path[i][j++]]->name);
			fflush(stdout);
		}
		i += 1;
		printf("\n");
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:53:52 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/20 21:25:19 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

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
	int i = 0;
	printf("[[ LINK ]]  ==> ");
	fflush(stdout);
	while (i < room->nb_link)
	{
		printf(_GREEN " [%d]" _RESET, room->link[i]);
		fflush(stdout);
		i += 1;
	}
	printf("\n");
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

void	ft_debug_line_adj_mat(int *line, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (line[i] == 0)
		{
			printf("[ %d ]", line[i]);
			fflush(stdout);
		}
		else
//		if (line[i] != 0)
		{
			printf("["_GREEN" %d "_RESET"]", line[i]);
			fflush(stdout);
		}
		i += 1;
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

void	ft_debug_path(t_map *data, int path[2][PRIME])
{
	int	len;
	int	i;

	len = path[0][0] + 1;
	i = 1;
	printf("[%d] ", path[0][0]);
	fflush(stdout);
	while (i < len)
	{
		printf("[%s]", data->rooms[path[0][i]]->name);
		fflush(stdout);
		i += 1;
	}
	i = 1;
	printf("\n");
	printf("[%d] ", path[1][0]);
	fflush(stdout);
	while (i < len)
	{
		printf("[%d]", path[1][i]);
		fflush(stdout);
		i += 1;
	}
	printf("\n\n");
}

void	ft_debug_tab_path(t_map *data)
{
	int	i;

	i = 0;
	printf("start = [ %s ] | end = [ %s ]\n", data->start->name, data->end->name);
	while (i < data->nb_path)
	{
		ft_debug_path(data, data->path_tab[i++]);
	}
}

void	ft_debug_opti(t_opti *opti)
{
	printf("#############################################\n");
	printf("index_p[0]      : ");
	ft_debug_line_adj_mat(opti->index_p[0], 60);
	fflush(stdout);
	printf("index_p[1]      : ");
	ft_debug_line_adj_mat(opti->index_p[1], 60);
	fflush(stdout);
	printf("len_p[0]        : ");
	ft_debug_line_adj_mat(opti->len_p[0], 60);
	fflush(stdout);
	printf("len_p[1]        : ");
	ft_debug_line_adj_mat(opti->len_p[1], 60);
	fflush(stdout);
	printf("distrib_p[0]    : ");
	ft_debug_line_adj_mat(opti->distrib_p[0], 60);
	fflush(stdout);
	printf("distrib_p[1]    : ");
	ft_debug_line_adj_mat(opti->distrib_p[1], 60);
	fflush(stdout);
	printf("Nombre de tour [ %d ]\n", opti->res);
	printf("#############################################\n");
}

void	ft_debug_queue(t_queue c_queue)
{
	size_t	i;

	i = 0;
	while (i < c_queue.index)
	{
		printf("[ %s ]\n", c_queue.queue[i]->name);
		i += 1;
	}
}

/*
	Fonction qui print un chemin depuis la matrix.
*/

static void	ft_print_path_matrix(t_map *data, int **adj_mat, int index)
{
	int	end_i;

	end_i = data->end->index;
	printf("[start] [%s]", data->rooms[index]->name);
	fflush(stdout);
	while (index != end_i)
	{
		index = ft_go_to_next(adj_mat, data->rooms[index], BLOCKED, BLOCKED);
		printf("[%s]", data->rooms[index]->name);
		fflush(stdout);
	}
	printf("\n");
}

/*
	Fonction qui va printer tout les paths depuis la matrix.
*/

void	ft_get_path_matrix(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_link;

	i = 0;
	nb_link = data->start->nb_link;
	while (i < nb_link)
	{
		if (adj_mat[START][data->start->link[i]] == BLOCKED)
			ft_print_path_matrix(data, adj_mat, data->start->link[i]);
		i += 1;
	}
	printf("\n");
}

/*
void	ft_bubble_sort(int *tab_l, int *tab_i, int len)
{
	int i;
	int j;
	int	i_min;
	int	min;
	int	tmp;

	i_min = 0;
	i = 0;
	while (i < len)
	{
		min = tab_l[i];
		i_min = i;
		j = i + 1;
		while (j < len)
		{
			if (tab_l[j] < min)
			{
				min = tab_l[j];
				i_min = j;
			}
			j += 1;
		}
		tab_l[i_min] = tab_l[i];
		tmp = tab_i[i_min];
		tab_i[i_min] = tab_i[i];
		tab_l[i] = min;
		tab_i[i] = tmp;
		i += 1;
	}
}
*/

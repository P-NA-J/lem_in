/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/16 18:44:54 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	ft_debug_single_path(int *path, size_t len);
void		print_info(t_map *data);
void	ft_reset_matrix(t_map *galery);

int		ft_get_number_pipe(int *line, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (line[i] == 1)
			count += 1;
		i += 1;
	}
	return (count);
}

void    ft_get_path(int **adj_mat, int i, int j, int len, t_map *galery)
{
    int tmp;
    printf("[%s]", galery->rooms[j]->name);
    fflush(stdout);
	if (j == 1)
		return ;
    tmp = i;
    i = j;
    j = 0;
    while (j < len)
    {
        if (adj_mat[i][j] == 1 && j != tmp)
            ft_get_path(adj_mat, i, j, len, galery);
		if (i == galery->end->index)
			return ;
		j += 1;
    }
}

int		ft_check_no_path(int **adj_mat, t_map *galery)
{
	if (ft_get_number_pipe(adj_mat[galery->start->index], galery->nb_rooms) == 0)
		return (FALSE);
	if (ft_get_number_pipe(adj_mat[galery->end->index], galery->nb_rooms) == 0)
		return (FALSE);
	return (TRUE);
}

void	ft_print_error(void)
{
	ft_putendl_fd("ERROR", 2);
}

void	ft_trivial_print(t_map *galery)
{
	int i;
	int	nb_ants;

	nb_ants = galery->nb_ants;
	i = 1;
	while (i < nb_ants)
	{
		ft_putstr("L");
		ft_putnbr(i);
		ft_putchar('-');
		ft_putstr(galery->end->name);
		ft_putchar(' ');
		i += 1;
	}
	ft_putstr("L");
	ft_putnbr(i);
	ft_putchar('-');
	ft_putstr(galery->end->name);
	ft_putchar('\n');
}

int		ft_check_trivial_path(int **adj_mat, t_map *galery)
{
	if (adj_mat[galery->start->index][galery->end->index] == 1)
		return (TRUE);
	return (FALSE);
}

void    ft_print_path(int **adj_mat, int len, t_map *galery)
{
    int i;

    i = 0;
	if (ft_check_no_path(adj_mat, galery) == FALSE)
		return (ft_print_error());
	if (ft_check_trivial_path(adj_mat, galery) == TRUE)
		return (ft_trivial_print(galery));
    while (i < len)
    {
        if (adj_mat[galery->start->index][i] == 1)
		{
			printf("[%s]", galery->start->name);
			fflush(stdout);
			ft_get_path(adj_mat, galery->start->index, i, len, galery);
			printf("\n");
		}
		i += 1;
   }
}

void	ft_res_matrix(t_map *galery)
{
	int i;
	int	nb_rooms;
	int	j;

	i = 0;
	nb_rooms = galery->nb_rooms;
	while (i < nb_rooms)
	{	
		j = 0;
		while (j < nb_rooms)
		{
			if (galery->adj_mat[i][j] == 1)
				galery->adj_mat[i][j] = 0;
		}
	}
}

int		ft_get_min_pipe(t_map *galery)
{
	int	min_start;
	int	min_end;

	min_start = ft_get_number_pipe(galery->adj_mat[galery->start->index], galery->nb_rooms);
	min_end = ft_get_number_pipe(galery->adj_mat[galery->end->index], galery->nb_rooms);
//	printf("min_start = %d\n", min_start);
//	printf("min_end = %d\n", min_end);
	return (min_start < min_end ? min_start : min_end);
}

void	ft_mult_bfs(t_map *galery, int **adj_mat)
{
	int	**tab_path;
	int i;
	int	j;
	int	min;
	int	*collision;
	
	min = ft_get_min_pipe(galery);
	if (!(tab_path = (int **)malloc(sizeof(int *) * min)))
		return ;
	i = 0;
	while ((tab_path[i] = ft_bfs(galery, adj_mat, galery->start)) != NULL && i < min)
	{
		ft_debug_single_path(tab_path[i], tab_path[i][0], galery);
	}
	if (i == min)
		ft_res_matrix(galery);
	else
		ft_reset_matrix(galery);
//	print_info(galery);
//	ft_print_path(adj_mat, galery->nb_rooms, galery);
}

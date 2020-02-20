/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 21:02:13 by aboitier          #+#    #+#             */
/*   Updated: 2020/02/07 21:45:02 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

# define START 0

int		count_nb_ways(int **adj_mat, int nb_rooms)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (i < nb_rooms)
	{
		if (adj_mat[START][i] > 0)
			count++;
		i++;
	}
	return (count);
}

int		get_total_size(int **adj_mat, int nb_rooms)
{
	int	i;
	int l;

	i = 0;
	l = 0;
	while (i < nb_rooms)
	{
		if (adj_mat[START][i] > 0)
			l+= adj_mat[START][i];
		i++;
	}

	return (TRUE);
}

int		print_result(t_map *data, int **adj_mat, int max_turn, int max_ants_per_way)
{
	int first = 0;
	int last = 0;

	int entered;
	int left;

	int	nb_turns;
	int	nb_ways;

	int remaining = 0;
	int turn_pass = 0;

	nb_ways = count_nb_ways(adj_mat, data->nb_rooms);
	nb_turns = 0;

	get_ways();
	while (last < data->nb_ants && nb_turns < max)
	{
		entered = 0;
		left = 0;
		turn_pass = 0;

		while (last + turn_pass < data->nb_ants && turn_pass < nb_ways)
		{
			if (last + nb_ways < ant_getting_in)
				entered += turn_pass;
			if (ant_reaching_end)
				left++;
			print_first_to_last(first, last, data);
			turn_pass++;
		}

		first += left;
		last += entered;
		remaining = data->nb_ants - last;
		nb_turns++;
	}	
	printf("%d\n", nb_turns);

//	send one ant per path;
		
//	earliest ant to get in
//		data->earliest
//	last ant to get in
//		data->latest
//	while (last ant to get in is inside != nb_ants)
//	printf("L-%ant_number-%roomname")
	return (TRUE);
}

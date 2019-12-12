/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 22:26:53 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/12 18:13:53 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		print_info(t_map *data)
{	
	int x = 0;
	int y = 0;
	int i = 0;

	printf("NB_ROOMS = %d\n", data->nb_rooms);
	while (i < data->nb_rooms)
	{
		printf("[%d]\t%s\t%d\n", i, (data->rooms[i])->name, (data->rooms[i])->hash);
		i++;
	}

	while (y < data->nb_rooms)
	{
    	x = 0;
    	while (x < data->nb_rooms)
    	{
			if (data->adj_mat[y][x] >= 1)
        		printf("["_RED"%d"_RESET"]", data->adj_mat[y][x]);
			else if (x == y)
				printf("["_GREEN"\\"_RESET"]");
			else
        		printf("[%d]", data->adj_mat[y][x]);
        	x++;
		}
    	printf("\n");
    	y++;
    }
	return (TRUE);
}

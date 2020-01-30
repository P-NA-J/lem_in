/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 22:26:53 by aboitier          #+#    #+#             */
/*   Updated: 2020/01/24 16:32:17 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

//char	colors[10][15] = {
//		colors[0] = "_RED",
//		colors[8] = "hello",
//		colors[1] = "_GREEN",
//		colors[2] = "_YELLOW",
//		colors[3] = "_BLUE ",
//		colors[4] = "_MAGENTA",
//		colors[5] = "_CYAN",
//		colors[6] = "_RESET"
//};

void	rooms_list(t_map *data)
{
	for (int i = 0; i < data->nb_rooms; i++)
		printf("[%d]\t%s\t%d\n", i, (data->rooms[i])->name, (data->rooms[i])->hash);
   	printf("\n");
}


int		new_mat_print(t_map *data)
{	
	int x = 0;
	int y = 0;

	while (y < data->nb_rooms)
	{
    	x = 0;
    	while (x < data->nb_rooms)
    	{
			if (data->adj_mat[y][x] >= 1)
        		printf("["_RED"%d"_RESET"]", data->adj_mat[y][x]);
			else if (x == y)
				printf("["_GREEN"\\"_RESET"]");
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

int		print_mat_old(t_map *data)
{	
	int x = 0;
	int y = 0;

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

void	print_info(t_map *data)
{
	printf("NB_ROOMS = %d\n", data->nb_rooms);
	printf("NB_ANTS = %d\n", data->nb_ants);
	//data->colors = get_colors();
 	rooms_list(data);
//	print_mat_old(data);
	new_mat_print(data);

}

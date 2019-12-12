/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/10 18:20:06 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>

int				get_nb_ants(t_map *data, char *buffer)
{
	char	*nb_ants;
	int		i;

	nb_ants = NULL;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (ft_isdigit((int)buffer[i]) == 0)
        	return (FALSE);
		if (i == 300)
			return (FALSE);
		i++;
	}
	if ((nb_ants = ft_strcsub(data->preparse->buffer, '\n')) == NULL)
		return (FALSE);
	data->preparse->buffer = data->preparse->buffer + i + 1;
	// add ft_atol
	return (ft_atoi(nb_ants));
}

t_room			*parse_comment(t_preparse *prep, t_map *data)
{
	int 	size;
	char	*tmp;

	tmp = NULL;
	if (prep->buffer[1] && prep->buffer[1] == '#')
	{
		if (!(tmp = ft_strcsub(prep->buffer, '\n')))
			return (NULL);
		size = ft_strlen(tmp);
		prep->buffer = prep->buffer + size + 1;	
		if (ft_strncmp((const char *)tmp, "##start", size) == 0)
			return (get_next_room(prep, data, 1));
		else if (ft_strncmp((const char *)tmp, "##end", size) == 0)
			return (get_next_room(prep, data, 2));
		else
			return (get_next_room(prep, data, 0));
		free(tmp);
	}
	return (NULL);	
}
/*
t_room			**malloc_neighbors(t_map *data)
{
	t_room		**neighbors;

	neighbors = NULL;
	if (!(neighbors = (t_room **)ft_memalloc(sizeof(t_room *) * data->nb_rooms)))
		return (NULL);
	return (neighbors);
}

int				add_neighbor(t_room *father, t_room *child)
{
	t_room	*tmp_father;	
	t_room	*tmp_child;	

	tmp_father = father;
	tmp_child = child;

	tmp_child->next = NULL;


	while (tmp_father->next != NULL)
		tmp_father = tmp_father->next;
	tmp_father->next = child;
	return (TRUE);
}

t_room			**get_neighbors(t_map *data)
{
	int 	x;
	int		empty;
	t_room	**neighbors;

	if (!(neighbors = malloc_neighbors(data)))
		return (NULL);
	empty = 0;
	x = 0;
	data->rooms[0]->features |= ADDED_NEIGHBORS;
	neighbors[0] = data->rooms[0];
	while (x < data->nb_rooms)
	{
		if (data->adj_mat[0][x] == 1)
		{	
			while (neighbors[empty] != NULL)
				empty++;	
			data->rooms[x]->features |= ADDED_NEIGHBORS;
			neighbors[empty] = data->rooms[x];
	//		add_neighbor(neighbors[0], data->rooms[x]);
		}
		x++;
	}
	int curr_room = 1;
	int index;
	while (curr_room < data->nb_rooms)
	{	 
		index = neighbors[curr_room]->index;	
		x = 0;
		while (x < data->nb_rooms)
		{
			if (data->adj_mat[index][x] == 1) 
			{
				if ((data->rooms[x]->features & ADDED_NEIGHBORS) == FALSE)
				{
					while (neighbors[empty] != NULL)
						empty++;
					data->rooms[x]->features |= ADDED_NEIGHBORS;
					neighbors[empty] = data->rooms[x];
				}

//				add_neighbor(neighbors[index], data->rooms[x]);

			}
			x++;
		}
		curr_room++;
	}

	return (neighbors);

}
*/

// put start at the beginning of the rooms table
// put end at the end of the rooms table
t_map			*parser(void)
{
	t_map		*data;
	char		*tmp;

	if (!(data = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if ((data->preparse = pre_parser()) == NULL)
		return (NULL);
	tmp = data->preparse->buffer;
	if ((data->nb_ants = get_nb_ants(data, data->preparse->buffer)) == FALSE) 
		return (NULL);
	if ((data->rooms = get_rooms(data, data->preparse)) == NULL)
		return (NULL);
	if (get_pipes(&data, data->preparse) == FALSE)
		return (NULL);
//	if ((data->neighbors = get_neighbors(data)) == NULL)
//		return (NULL);
//	printf("%s\n", tmp);

	free(tmp);
//	printf("%d\n", data->nb_ants);
//	printf("%s\n", data->preparse->buffer);
//	printf("line = %s\n", data->buffer);
//	
	return (data);
}

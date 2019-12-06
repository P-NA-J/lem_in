/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/06 23:42:01 by aboitier         ###   ########.fr       */
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
//	printf("%s\n", tmp);

	free(tmp);
//	printf("%d\n", data->nb_ants);
//	printf("%s\n", data->preparse->buffer);
//	printf("line = %s\n", data->buffer);
//	
	int i = 0;
	printf("NB_ROOMS = %d\n", data->nb_rooms);
	while (i < data->nb_rooms)
	{
		printf("[%d]\t%s\t%d\n", i, (data->rooms[i])->name, (data->rooms[i])->hash);
		i++;
	}
	int x = 0;
	int y = 0;
	while (y < data->nb_rooms)
	{
		x = 0;
		while (x < data->nb_rooms)
		{
			printf("[%d]", data->adj_mat[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	return (data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:16:41 by aboitier          #+#    #+#             */
/*   Updated: 2020/01/30 15:45:05 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//free:
//data
//data->preparse
//data->preparse->parser
//
//data->t_rooms[*][*]
//data->t_rooms[*]
//
//data->adj_mat[*][*]
//data->adj_mat[*]

#include "../../includes/lem_in.h"
void	free_rooms(t_map *data)
{
	int i;
	
	i = 0;
	while (i < data->nb_rooms && data->rooms[i])
	{
		free(data->rooms[i]->name);
		free(data->rooms[i]);
		i++;
	}
	free(data->rooms);
}

void	free_preparse(t_map *data)
{
	if (data->preparse->buffer)
		free(data->preparse->tmp_buff);
	free(data->preparse);
}

void	free_adj_mat(t_map *data)
{
	int y;

	y = 0;
	while (y < data->nb_rooms && data->adj_mat[y])
	{
		free(data->adj_mat[y]);
		y++;
	}
	free(data->adj_mat);
}

void	free_all(t_map *data)
{
	if (data->preparse)
		free_preparse(data);
	if (data->rooms)
		free_rooms(data);
	if (data->adj_mat)
		free_adj_mat(data);
	free(data);
}

t_map	*which_error(t_map *data, int type)
{
	t_map	*error;
	int		err;
	
	error = data;
	err = 0;
	if (type == 1)
	{
		while (err != 2)
			if (*data->preparse->buffer-- == '\n')
				err++;
		data->preparse->buffer++;
		*data->preparse->buffer++ = '\0';	
		return (error);
	}
	else if (type == 2)
	{
		free_all(data);
		ft_putstr("ERROR\n");
	}
	return (NULL);
}

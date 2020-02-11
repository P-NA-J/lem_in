/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 10:31:56 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/11 14:28:30 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_list_push_back(t_path **head, t_path *node)
{
	t_path *head_ref;
	t_path	*head_tmp;

	head_tmp = *head;
	head_ref = *head;
	if (!head || !node)
		return ;
	if (head_ref == NULL)
	{
		*head = node;
		return ;
	}
	else
	{
		while (head_ref->next != NULL)
			head_ref = head_ref->next;
		head_ref->next = node;
	}
	*head = head_tmp;
}

t_path	*ft_create_node(int index, int **adj_mat, int nb_rooms)
{
	t_path	*node;
	int		len;
	int		i;

	if (!(node = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	node->len = adj_mat[0][index] + 1;
	len = node->len;
	node->path[0] = START;
	i = 1;
	while (i < len)
	{
		node->path[i] = index;
		index = ft_go_to_next(adj_mat[index], nb_rooms);
		i += 1;
	}
	node->next = NULL;
	return (node);
}

void	ft_set_path_info(t_path *path_list, t_map *data)
{
	data->nb_path = 0;
	data->sum_len_path = 0;
	while (path_list != NULL)
	{
		data->nb_path += 1;
		data->sum_len_path += path_list->len;
		path_list = path_list->next;
	}
}

t_path	*ft_path(t_map *data, int **adj_mat)
{
	int	i;
	t_path	*path_list;
	t_path	*node;

	path_list = NULL;
	i = 0;
	while (i < data->start->nb_link)
	{
		node = ft_create_node(data->start->link[i], adj_mat, data->nb_rooms);
		ft_list_push_back(&path_list, node);
		i += 1;
	}
	ft_set_path_info(path_list, data);
	return (path_list);
}
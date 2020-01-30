void	ft_adj_mat_line_process(t_map *data, int **adj_mat,
							t_queue *bfs_q_ref, t_room *current)
{
	int	nb_branch;
	int	i;
	int	tmp;

	i = -1;
	nb_branch = ft_occurence_count(data, adj_mat[current->index], 1, data->nb_rooms);
	if (adj_mat[current->index][data->end->index] == 1)
	{
		ft_add_front_queue(bfs_q_ref, data->end, current);
		return ;
	}
	while (++i < data->nb_rooms)
	{
		if (adj_mat[current->index][i] == UNCHANGED)
		{
			if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 4)) != FALSE)
			{
				continue ;
			}
			else if ((tmp = ft_check_line(adj_mat[i], data->nb_rooms, 3)) != FALSE && nb_branch == 1)
			{
				if (data->rooms[i]->time > (current->time + 1))
				{
					data->rooms[i]->time = current->time + 1;
					data->rooms[i]->prev = current;
					ft_add_queue(bfs_q_ref, data->rooms[tmp], data->rooms[i], -1);
				}
			}
			else if (ft_line_check(adj_mat[i], data->nb_rooms) == -1)
			{
				ft_add_queue(bfs_q_ref, data->rooms[i], current, 1);
			}
		}
		if (adj_mat[current->index][i] == 3)
			if (nb_branch == 1)
				ft_add_queue(bfs_q_ref, data->rooms[i], current, -1);
	}
}
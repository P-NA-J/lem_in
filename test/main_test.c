#include "../includes/lem_in.h"
#include <stdarg.h>

void	ft_debug_room(t_room *room, int mode);
void	ft_debug_rooms(t_room **rooms, size_t size, int mode);
void	ft_debug_queue(t_queue bfs_queue);
void	ft_debug_adj_mat(int **adj_mat, size_t size);
void	ft_print_char_line(char c, size_t n);

# define FULL     1
# define RESTRICT 0

t_room	ft_room_create(char *name, int index, int features, t_room *prev)
{
	t_room	room;

	room.name = name;
	room.index = index;
	room.features = features;
	room.prev = prev;
	return (room);
}

t_room *ft_room_ref_create(char *name, int index, int features, t_room *prev)
{
	t_room *ref;

	if(!(ref = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	*ref = ft_room_create(name, index, features, prev);
	return (ref);
}

t_map	ft_map_create(t_room *start, t_room *end, t_room **rooms,
					int nb_ants, int nb_rooms)
{
	t_map	map;

	map.start = start;
	map.end = end;
	map.rooms = rooms;
	map.nb_ants = nb_ants;
	map.nb_rooms = nb_rooms;
	return (map);
}

t_map	*ft_map_ref_create(t_room *start, t_room *end, t_room **rooms,
					int nb_ants, int nb_rooms)
{
	t_map	*ref;

	if (!(ref = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	*ref = ft_map_create(start, end, rooms, nb_ants, nb_rooms);
	return (ref);
}

int **ft_adj_mat_create(size_t len)
{
	int **adj_mat;
	size_t	i;

	i = 0;
	if (!(adj_mat = (int **)malloc(sizeof(int *) * len)))
		return (0);
	while (i < len)
	{
		if (!(adj_mat[i++] = (int *)malloc(sizeof(int) * len)))
			return (0);
	}
	return (adj_mat);
}

int main()
{
	t_map	*galery;
	int		**adj_mat;
	t_queue	bfs_queue;
	int		i;

	i = 0;
	
	if (!(galery->rooms = (t_room **)malloc(sizeof(t_room *) * galery->nb_rooms)))
	{
		puts("/!\\ MALLOC FAILURE /!\\");
		return (0);
	}
	galery->rooms[0] = ft_room_ref_create("A", 0, IS_START, NULL);
	ft_debug_room(galery->rooms[0], RESTRICT);

	galery->rooms[1] = ft_room_ref_create("B", 1, UNCHANGED, NULL);
//	ft_debug_room(galery->rooms[1], RESTRICT);

	galery->rooms[2] = ft_room_ref_create("C", 2, UNCHANGED, NULL);
//	ft_debug_room(galery->rooms[2], RESTRICT);

	galery->rooms[3] = ft_room_ref_create("D", 3, UNCHANGED, NULL);
//	ft_debug_room(galery->rooms[3], RESTRICT);

	galery->rooms[4] = ft_room_ref_create("E", 4, UNCHANGED, NULL);
//	ft_debug_room(galery->rooms[4], RESTRICT);

	ft_debug_galery(galery);
	return (0);
}
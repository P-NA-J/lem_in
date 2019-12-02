/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/02 20:19:35 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>

//static void		ft_add_line(t_list **data, char **tmp)
//{
//	char		*line;
//
//	line = ft_strpdupf(*tmp, '\n', tmp);
//	ft_lst_push_back(data, line, ft_strlen(line));
//	free(line);
//}

char			*ft_strcsub(char *s, char c)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (s[j] && j < i)
	{
		new[j] = s[j];
		j++;
	}
	new[j] = '\0';	
	return (new);
}

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

int				get_nb_rooms(char *buffer)
{
	int		nb_rooms;
	int		i;
	
	nb_rooms = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '-')
	{
		if (buffer[i] == '\n')
			nb_rooms++;
		i++;
	}	
	return (nb_rooms);
}

t_room			**get_rooms(t_map *data, char *buffer)
{
	t_room	**rooms;

	rooms = NULL;
	if ((data->nb_rooms = get_nb_rooms(buffer)) == 0)
		return (FALSE);
	printf("%d\n", data->nb_rooms);
	return (rooms);
}

t_map			*parser(void)
{
	t_map		*data;

	if (!(data = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	if ((data->preparse = pre_parser()) == NULL)
		return (NULL);
	if ((data->nb_ants = get_nb_ants(data, data->preparse->buffer)) == FALSE) 
		return (NULL);
	if ((data->rooms = get_rooms(data, data->preparse->buffer)) == NULL)
		return (NULL);
//	printf("%d\n", data->nb_ants);
	
	printf("%s\n", data->preparse->buffer);

	//printf("line = %s\n", data->buffer);

	free(data->preparse->buffer);
	free(data->preparse);

//		tmp = ft_strjoinf(tmp, line, 1);
//		while (ft_strchr(tmp, '\n') != NULL || tmp != NULL)
//			ft_add_line(&data, &tmp);
	return (data);
}

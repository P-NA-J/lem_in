/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboitier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 22:02:40 by aboitier          #+#    #+#             */
/*   Updated: 2019/12/05 19:06:09 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

char		*increase_buffer(t_preparse *data, int reload)
{
	char	*new_buffer;

	new_buffer = NULL;
	if (!(new_buffer = (char *)malloc(sizeof(char) * BASE_MALLOC * reload)))
		return (NULL);
	new_buffer = ft_strcpy(new_buffer, data->buffer);
	free(data->buffer);
	return (new_buffer);
}

int			check_first_lines(char *buffer)
{
	int i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (ft_isdigit((int)buffer[i]) == 0)
			return (FALSE);
		if (i == 300)
			return (FALSE);
		i++;
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] == ' ')
			spaces++;
		if (spaces > 2 || i > 1500)
			return (FALSE);
		i++;
	}
	return (TRUE);
}		

long		copy_fr_index(t_preparse *data, char *src, long index)
{
	int	i;
	
	i = 0;
	while (src[i] != '\0')
	{
		data->buffer[index] = src[i];
		index++;
		i++;
	}
	data->buffer[index] = '\0';
	return (index);
}

t_preparse		*pre_parser(void)
{
	t_preparse	*data;
	char		buff[BUFF_SIZE + 1];
	int			ret;

	if (!(data = (t_preparse *)malloc(sizeof(t_preparse))))
		return (NULL);
	ft_bzero(data, sizeof(t_preparse));
	data->reload = 1;
	if (!(data->buffer = (char *)malloc(sizeof(char) * BASE_MALLOC)))
		return (NULL);
	while ((ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		data->size += ret;
		if (data->size >= (long)BASE_MALLOC * data->reload)
			data->buffer = increase_buffer(data, ++data->reload);
		data->curr_index = copy_fr_index(data, buff, data->curr_index);
		if (data->reload == 10)
			if (check_first_lines(data->buffer) == FALSE)	
				return (NULL);
	}
	return (data);
}

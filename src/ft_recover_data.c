/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/19 15:57:43 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>

static void		ft_add_line(t_list **data, char **tmp)
{
	char		*line;

	line = ft_strpdupf(*tmp, '\n', tmp);
	ft_lst_push_back(data, line, ft_strlen(line));
	free(line);
}

t_list			*ft_recover_data(void)
{
	t_list		*data;
	int			ret;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	t_bool		ward;

	tmp = NULL;
	data = NULL;
	ward = 0;
	while ((ret = read(0, buff, BUFF_SIZE)) >= 0)
	{
		if (ret == 0)
			return (data);
		buff[ret] = 0;
		tmp = ft_strjoinf(tmp, buff, 1);
		while (ft_strchr(tmp, '\n') != NULL || tmp != NULL)
			ft_add_line(&data, &tmp);
	}
	return (data);
}

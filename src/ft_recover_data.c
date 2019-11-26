/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recover_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:33:58 by pauljull          #+#    #+#             */
/*   Updated: 2019/11/26 21:46:02 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdlib.h>

static void		ft_add_line(t_list **data, char **tmp)
{
	char		*line;

	printf("TMP = %s\n", *tmp);
	line = ft_strpdupf(*tmp, '\n', tmp);
	printf("LINE = %s\n", line);
	ft_lst_push_back(data, line, ft_strlen(line));
	free(line);
}

t_list			*ft_recover_data(void)
{
	t_list		*data;
	char		*line;
	char		*tmp;

	tmp = NULL;
	data = NULL;
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		tmp = ft_strjoinf(tmp, line, 1);
		while (ft_strchr(tmp, '\n') != NULL || tmp != NULL)
			ft_add_line(&data, &tmp);
	}
	return (data);
}

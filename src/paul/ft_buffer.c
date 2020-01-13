/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:48:59 by pauljull          #+#    #+#             */
/*   Updated: 2020/01/08 17:53:56 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	ft_flush_buffer(t_buff *buff)
{
	write(1, buff->buff, buff->i);
	ft_bzero(buff->buff, BUFF_SIZE + 1);
	buff->i = 0;
}

void	ft_putstr_buffer(t_buff *buff, char *str, int len)
{
	while (len > (BUFF_SIZE - buff->i))
	{
		len -= BUFF_SIZE - buff->i;
		ft_strncpy(buff->buff + buff->i, str, BUFF_SIZE - buff->i);
		str += BUFF_SIZE - buff->i;
		buff->i += BUFF_SIZE - buff->i;
		ft_flush_buffer(buff);
	}
	if (len)
	{
		ft_strncpy(buff->buff + buff->i, str, len);
		buff->i += len;
	}
}

void	ft_write_in_buffer(t_buff *buff, char c, int len)
{
	while (len > (BUFF_SIZE - buff->i))
	{
		len -= BUFF_SIZE - buff->i;
		while (buff->i < BUFF_SIZE)
		{
			buff->buff[buff->i] = c;
			buff->i += 1;
		}
		ft_flush_buffer(buff);
	}
	while (len)
	{
		buff->buff[buff->i] = c;
		buff->i += 1;
		len -= 1;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:51:52 by pauljull          #+#    #+#             */
/*   Updated: 2019/12/09 00:07:48 by aboitier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H

# define FUNCTION_H

typedef int t_bool;

t_map		*parser(void);
t_preparse	*pre_parser(void);
t_bool		ft_parsing(t_list *data, t_map *galery);
uint32_t	jenkins_hash(char *name);
t_room		*get_next_room(t_preparse *prep, t_map *data, int opt);
t_room		**get_rooms(t_map *data, t_preparse *prep);
t_room		*parse_comment(t_preparse *prep, t_map *data);
int			get_pipes(t_map **data, t_preparse *prep);

char		*ft_passing_name(char *str);
t_bool		ft_is_comment(char *str, t_bool condition);
t_bool		ft_is_room(char *str);
t_bool		ft_is_tube(char *str);
t_bool		ft_is_numb_str(char **str);

char		*ft_strcsub(char *s, char c);
int			count_char_until(char *str, char c, char u);

int			print_info(t_map *data);

#endif

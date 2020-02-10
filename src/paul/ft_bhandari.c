/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bhandari.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauljull <pauljull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 09:13:18 by pauljull          #+#    #+#             */
/*   Updated: 2020/02/10 12:31:20 by pauljull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

/*
	Cette fonction va mettre a 0 tout les liens excepté celui qui relie start à end.
*/

int **ft_s_to_e(t_map *data, int **adj_mat)
{
	int	i;
	int	nb_rooms;

	nb_rooms = data->nb_rooms;
	i = 0;
	while (i < nb_rooms)
	{
		ft_bzero(adj_mat[i], sizeof(int) * nb_rooms);
		i++;
	}
	adj_mat[data->start->index][data->end->index] = 1;
	return (adj_mat);
}

/*
	Copie de la première ligne de la matrice d'adjacence.
*/

int	*ft_tab_cpy(t_map *data, int **adj_mat)
{
	int	*tmp;

	tmp = ft_memalloc(sizeof(int) * data->nb_rooms);
	ft_memcpy(tmp, adj_mat[data->start->index], sizeof(int) * data->nb_rooms);
	ft_bubble_sort(tmp, data->nb_rooms);
	return (tmp);
}

/*
	Passe tout les NO_LINK pour renvoyer l'index de la première salle qui débute un chemin.
*/

int	ft_jump_to_sort_path(int *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] <= 0)
		i += 1;
	return (i);
}

/*
	Fonction qui va échanger de place deux int au sein d'un même tableau.
*/

void	ft_swap_int(int *tab, int i_1, int i_2)
{
	int	tmp;

	tmp = tab[i_1];
	tab[i_1] = tab[i_2];
	tab[i_2] = tmp;
}

/*
	Fonction qui va remettre toutes les valeurs non nulles au début du tableau.
*/

void	ft_left_slide(t_opti *op, int begin, int len)
{
	int	i;

	i = 0;
	while (begin < len)
	{
		ft_swap_int(op->tab, i, begin);
		i += 1;
		begin += 1;
	}
}

/*
	Initialise la structure opti
*/

void	ft_init_opti(t_opti *op, int **adj_mat, t_map *data)
{
	op->tab = ft_tab_cpy(data, adj_mat);
	op->nb_path = 0;
	op->sum = 0;
	op->max_len = 0;
	op->res = 0;
}

/*
	Fonction qui check si le chemin appartient au set de chemin optimal.
*/

int		ft_have_to_keep(int len, t_opti *op)
{
	int	i;

	i = 0;
	while (i < op->max_len)
	{
		if (len == op->tab[i])
		{
			op->tab[i] = -1;
			return (TRUE);
		}
		i += 1;
	}
	return (IGNORE);
}

/*
	Fonction qui supprime un lien d'un tableau de lien et réorganise tout les autres.
*/

void	ft_opti_erase_link(int *t_link, int i_link, int nb_link)
{
	while (i_link < nb_link)
	{
		t_link[i_link] = t_link[i_link + 1];
		i_link += 1;
	}
}

/*
	Fonction qui ne garde que les chemins formant le bon set de chemin.
*/

void	ft_opti_clean_matrix(t_map *data, int **adj_mat, t_opti *op)
{
	int	i;

	i = 0;
	while (i < data->start->nb_link)
	{
		if (ft_have_to_keep(adj_mat[START][data->start->link[i]], op) == IGNORE)
		{
			adj_mat[START][data->start->link[i]] = 0;
			ft_opti_erase_link(data->start->link, i, data->start->nb_link);
			data->start->nb_link -= 1;
		}
		i += 1;
	}
}

/*
	Fonction qui supprime les chemins en trop
*/

void	ft_opti_erase_path(t_opti *op)
{
	int	i;

	i = 0;
	while (op->tab[i] > 0)
	{
		while (i < op->nb_path)
			i += 1;
		op->tab[i] = 0;
		i += 1;
	}
}

/*
	fonction qui va remplir correctement la structure opti
*/

void	ft_optimize_matrix(t_map *data, t_opti *op)
{
	int	i;
	int	tmp_res;

	i = 0;
	while (op->tab[i] > 0)
	{
		op->nb_path += 1;
		op->sum += op->tab[i];
		tmp_res = (data->nb_ants + op->sum - op->nb_path) / op->nb_path;
		if (op->res == 0 || tmp_res < op->res)
		{
			op->res = tmp_res;
			op->max_len = op->tab[i];
		}
		else
		{
			op->nb_path -= 1;
			ft_opti_erase_path(op);
			return (ft_opti_clean_matrix(data, data->adj_mat, op));
		}
		i += 1;
	}
}

/*
	Minimise le nombre de tours en diminuant le set de chemins.
*/

void	ft_minimize_path(t_map *data, int **adj_mat)
{
	t_opti	op;
	int	i;

	ft_init_opti(&op, adj_mat, data);
	i = ft_jump_to_sort_path(op.tab);
	ft_left_slide(&op, i, data->nb_rooms);
	ft_optimize_matrix(data, &op);
}

/*
	Cette fonction va appeler en boucle le BFS afin de modeler le graphe.
	Entre chaque appel, on ré-initialise l'état des salle et on actualise le graphe.
*/

int		**ft_bhandari(t_map *data, int **adj_mat)
{
	if (adj_mat[data->start->index][data->end->index] == UNCHANGED)
		return (ft_s_to_e(data, adj_mat));
	while (ft_bfs(data, adj_mat) != NULL)
		ft_reset_matrix(data, adj_mat);
	ft_clean_matrix(data, adj_mat);
	ft_minimize_path(data, adj_mat);
	return (adj_mat);
}

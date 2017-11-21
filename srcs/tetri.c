/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:16:27 by fsabatie          #+#    #+#             */
/*   Updated: 2017/11/19 16:16:28 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/fill_it.h"
#include <stdlib.h>
#include <stdio.h>

t_etrimino	*ft_newtetri(char **tab, char letter)
{
	t_etrimino *tet;

	if (!(tet = (t_etrimino*)malloc(sizeof(t_etrimino))))
		return (NULL);
	tet->tetrimino = tab;
	tet->letter = letter;
	tet->next = NULL;

	return (tet);
}

void		ft_print_tetri(t_etrimino *tet)
{
	char **tetri;

	tetri = tet->tetrimino;
	while (*tetri)
		ft_putendl(*tetri++);
	ft_putendl("");
}

static int	*ft_get_space(char **tab)
{
	int *space;
	int x;
	int y;

	space = (int *)malloc(sizeof(int) * 2);
	x = 0;
	y = 0;

	while (!(strchr(tab[y], '#')))
		y++;
	space[1] = y;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (tab[x][y] == '#')
			{
				space[0] = y;
				return (space);
			}
			x++;
		}
		y++;
	}
	return (space);
}

void		ft_set_tetri(char **tab)
{
	int *pos;
	int i;
	int y;

	i = 0;
	pos = ft_get_space(tab);
	while (i < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (tab[i][y] == '#')
				ft_swap(&tab[i][y], &tab[i - pos[1]][y - pos[0]]);
			y++;
		}
		i++;
	}
}

int		ft_place_tetri(t_map *map, t_etrimino *tetrimino)
{
	char **tet;
	int i;
	int y;

	tet = tetrimino->tetrimino;
	tetrimino->x = map->x;
	tetrimino->y = map->y;
	i = 0;
	while (i < 4)
	{
		y = 0;
		while (y < 4)
		{
			if (tet[i][y] == '#')
				map->map[map->y + i][map->x + y] = tetrimino->letter;
			y++;
		}
		i++;
	}
	return (1);
}

void 	ft_rem_tetri(t_map *map, t_etrimino *tetrimino)
{
	int i;
	int y;
	char **toedit;

	toedit = map->map;
	i = 0;
	while (i < map->map_size)
	{
		y = 0;
		while (y < map->map_size)
		{
			if (toedit[i][y] == tetrimino->letter)
				toedit[i][y] = '.';
			y++;
		}
		i++;
	}
}

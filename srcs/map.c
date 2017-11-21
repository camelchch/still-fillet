/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 16:16:21 by fsabatie          #+#    #+#             */
/*   Updated: 2017/11/19 23:42:59 by fsabatie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/fill_it.h"
#include <stdlib.h>
#include <stdio.h>

t_map	*ft_newmap(t_map *prev_map, int mapsize)
{
	t_map *map;
	int i;

	i = 0;
	if (prev_map)
		free(prev_map);
	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	if (!(map->map = (char**)malloc(sizeof(char*) * mapsize + 1)))
		return (NULL);
	while (i < mapsize)
	{
		if (!(map->map[i] = (char*)malloc(sizeof(char*) * mapsize + 1)))
			return (NULL);
		ft_memset(map->map[i], '.', mapsize);
		i++;
	}
	map->map[i] = 0;
	map->map_size = mapsize;
	map->x = 0;
	map->y = 0;
	return (map);
}

int		ft_minmapsize(t_etrimino *tet)
{
	int count;
	int sqr;

	count = 0;
	sqr = 0;
	while ((tet = tet->next))
		count++;
	while (sqr * sqr < 4 * count)
		sqr++;
	return (sqr);
}

void		ft_print_map(t_map *map)
{
	char **toprint;

	toprint = map->map;
	while (*toprint)
		ft_putendl(*toprint++);
}

static int	ft_change_free(t_map *map)
{
	map->x++;
	if (map->x % map->map_size == 0)
	{
		map->x = 0;
		map->y++;
	}
	if (map->y == map->map_size)
		return (0);
	return (1);
}


int		ft_solve_map(t_map *map, t_etrimino *tetriminos, int x, int y)
{
//	printf("First tetri is %c\n", tetriminos->letter);
	map->x = x;
	map->y = y;
	t_etrimino *start;

	start = tetriminos;
	while (tetriminos)
	{

		while (!ft_check_piece(map, tetriminos))
		{
			//printf("Trying to put %c in map[%i][%i]\n", tetriminos->letter,  map->y, map->x);
			if (!ft_change_free(map))
			{
				if (tetriminos->letter == 'A')
				{
					//printf("Reached end of map, resizing the map\n");
					return ft_solve_map(ft_newmap(map, map->map_size + 1), start, 0, 0);
				}
				else
				{
					//printf("Reached end of map, removed the tetri %c and\ntrying to change the place of %c\n",tetriminos->prev->letter, tetriminos->prev->letter);
					ft_rem_tetri(map, tetriminos->prev);
					return ft_solve_map(map, tetriminos->prev, tetriminos->prev->x + 1, tetriminos->prev->y);
				}
			}
		}
		ft_place_tetri(map, tetriminos);
	//	printf("%c has been put in map[%i][%i]\n", tetriminos->letter, map->y, map->x);
		tetriminos = tetriminos->next;
		map->x = 0;
		map->y = 0;
	}
	return (1);
}

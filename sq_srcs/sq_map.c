/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:15:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/21 09:55:23 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "sq_fillit.h"
#include "../includes/libft/libft.h"

int		mini_sq(tetri_list *list)
{
	int			i;
	tetri_list	*temp;

	i = 1;
	temp = list;
	while (temp->next)
		temp = temp->next;
	while ( i * i <= (temp->letter - 'A' + 1) * 4)
		i++;
	return (i);
}

tetri_map	*new_map(int size)
{
	int			i;
	int			j;
	tetri_map	*newmap;

	i = -1;
	j = -1;
	if (!(newmap = (tetri_map *)malloc(sizeof(*newmap))))
		return (NULL);
	if(!(newmap->map = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	if(!(*(newmap->map) = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (++i < size)
	{
		while(++j < size)
			(newmap->map)[i][j] = '.';
	}
	newmap->size = size;
	newmap->add_map = newmap;
	return (newmap);
}

int		check_fill(char **map, int mpsize, tetri_list *list, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
			{
				if (x + i >= mpsize || y + j >= mpsize || map[x + i][y + j] != '.')
					return (0);
			}
			j++;
		}
	}
	return (1);
}

int		find_fit(char **map, int mpsize, tetri_list *list, int x, int y)
{
	int		i;
	int		j;

	i = x;
	j = y;
	while (!check_fill(map, mpsize, list, i, j) && i < mpsize)
	{
		j = 0;
		while (!check_fill(map, mpsize,list, i, j) && j < mpsize)
			j++;
		i++;
	}
	if (i < mpsize)
	{
		list->x = i;
		list->y = j;
		return (1);
	}
	return (0);
}


void	fill_map(char **map, tetri_list *list, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
				map[x + i][y + j] = list->letter;
			j++;
		}
	}
}

void	remove_onete(char **map, int mpsize, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mpsize)
	{
		j = 0;
		while (j < mpsize)
		{
			if (map[i][j] == c)
				map[i][j] = '.';
		}
	}
}

void		solve_map(tetri_map *map, tetri_list *list, int x, int y)
{
	tetri_list *head;

	head = list;
	printf("00000011222223333");
	while (list)
	{
		if (!find_fit(map->map, map->size, list, x, y))
		{
		printf("can't place %c\n",list->letter);
			list->x = 0;
			list->y = 0;
			if (list->letter == 'A')
				return solve_map(new_map(map->size + 1),head, head->x, head->y);
			remove_onete(map->map, map->size, list->pre->letter);

			return (solve_map(map, list->pre, list->pre->x + 1, list->pre->y));
		}
		printf("place %c in %d%d\n",list->letter,list->x, list->y);
		fill_map(map->map, list, list->x, list->y);
		list = list->next;
	}
}




/*
   int		fit_map(short int *map, int size_map, tetri_list *list)
   {
   int		x;
   int		y;

   x = 0;
   y = 0;
   while (x < size_map - list->length)
   {
   while (y < size_map - list->heigt)
   {
   if 
   */


int		main(int ac, char **av)
{
	tetri_list	*list;
	tetri_map	*map;

	if(ac != 2)
		ft_exit("not valid file number");

	list = ft_readfile(av[1]);
	map = new_map(mini_sq(list));
	printf("1111100000");
	solve_map(map,list, list->x, list->y);
	/*
	printf("2222220000");


	int	i = 0;
	int	j = 0;
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			printf("%c",map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	*/
	return (0);
}


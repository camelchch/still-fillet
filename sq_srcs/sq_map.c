/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:15:35 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/23 18:33:31 by saxiao           ###   ########.fr       */
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
	while ( i * i < (temp->letter - 'A' + 1) * 4)
		i++;
	return (i);
}

tetri_map	*new_map(int size)
{
	int			i;
	int			j;
	tetri_map	*newmap;

	i = -1;
	if (!(newmap = (tetri_map *)malloc(sizeof(*newmap))))
		return (NULL);
	if(!(newmap->map = (char **)malloc(sizeof(char *) * size)))
		return (NULL);
	while (++i < size)
	{
		if(!((newmap->map)[i] = (char *)malloc(sizeof(char) * size)))
			return (NULL);
		j = -1;
		while(++j < size)
			(newmap->map)[i][j] = '.';
	}
	newmap->size = size;
	newmap->add_map = newmap;
	return (newmap);
}

int		check_fill(char **map, int mpsize, tetri_list *list, int x, int y)
{
	ft_putstr("check fit for ");
	ft_putchar(list->letter);
	ft_putendl("");
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
				//ft_putnbr(mpsize);
			}
			j++;
		}
	}
	ft_putendl("no problem heree this position doesnt work 88888");
	return (1);
}

int		find_fit(char **map, int mpsize, tetri_list *list)
{
	int		x;
	int		y;
	int		test;

	x = list->x;
	y = list->y;
	ft_putstr("trying to find a place for ");
	ft_putchar(list->letter);
	ft_putendl("");
		ft_putnbr(x);
		ft_putnbr(y);
	ft_putendl("");
	while ( x  < mpsize)
	{
		ft_putnbr(x);
		ft_putnbr(y);
		while (y < mpsize)
		{
			ft_putnbr(y);
			test = (check_fill(map, mpsize, list, x, y));
			if (test)
			{
				ft_putnbr(y);
				list->x = x;
				list->y = y;
				ft_putstr("find a place for");
				ft_putchar(list->letter);
				ft_putendl("");
				return (1);
			}
			y++;
		}
		x++;
		y = 0;
	}
	//ft_putstr("DID NOT find a place for");
	//ft_putchar(list->letter);
	//ft_putendl("");
	return (0);
}


void	fill_map(char **map, tetri_list *list)
{
	//	ft_putchar(list->letter);
	//	ft_putendl("");
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if((list->str)[i][j] == '#')
				map[list->x + i][list->y + j] = list->letter;
			j++;
		}
	}
}

void	remove_onete(char **map, int mpsize, tetri_list *list)
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
			if (map[i][j] == list->letter)
				map[i][j] = '.';
			j++;
		}
		i++;
	}
	if (list->y < mpsize - 1)
		list->y++;
	if (list->y == mpsize - 1)
	{
		list->x++;
		list->y = 0;
	}
}

void	print_map(char **map, int size)
{
	int i = 0;
	int j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_putchar(map[i][j]);
			j++;
		}
		ft_putendl("");
		i++;
	}
}

int		solve_map(tetri_map *map, tetri_list *list)
{
	tetri_list *head;

	head = list;
	if (list)
	{
		//ft_putstr("curent ");
		//ft_putchar(list->letter);
		//ft_putstr(" is in position  ");
		//ft_putnbr(list->x);
		//ft_putstr(" ");
		//ft_putnbr(list->y);
		//ft_putendl("");
		if (!find_fit(map->map, map->size, list))
		{
		//	ft_putstr("curent ");
		//	ft_putchar(list->letter);
		//	ft_putstr("did not find a position ");
			list->x = 0;
			list->y = 0;
			if (list->letter == 'A')
				return (0);
			remove_onete(map->map, map->size, list->pre);
		//	ft_putstr("previous ");
		//	ft_putchar(list->pre->letter);
		//	ft_putstr(" is in position  ");
		//	ft_putnbr(list->pre->x);
		//	ft_putstr(" ");
		//	ft_putnbr(list->pre->y);
		//	ft_putendl("");

			list = list->pre;
		}
		else
		{
		fill_map(map->map, list);
		if (!list->next)
			return (1);
		/*if (!list->next)
		{
				print_map(map->map, map->size);
			exit  (0);
		}
		*/
		//ft_putstr("next ");
		//ft_putchar(list->next->letter);
		//ft_putstr(" is in position  ");
		//ft_putnbr(list->next->x);
		///ft_putstr(" ");
		//ft_putnbr(list->next->y);
		return (solve_map(map,list->next));
		//print_map(map->map, map->size);
		//	else
	}
}
	return (1);
}

int		main(int ac, char **av)
{
	tetri_list	*list;
	tetri_map	*n_map;
	tetri_map	*temp;

	if(ac != 2)
		ft_exit("not valid file number");
	list = ft_readfile(av[1]);
	n_map = new_map(mini_sq(list));
	//int k = check_fill(n_map->map, 4, list, list->x, list->y);
	//ft_putstr("not problem1111100000");
	while (!solve_map(n_map,list))
	{
	temp = n_map;
	n_map = new_map(temp->size + 1);
	free (temp);
	}
				print_map(n_map->map, n_map->size);

	//printf("2222220000");
	//print_map(n_map->map, n_map->size);
	return (0);
}

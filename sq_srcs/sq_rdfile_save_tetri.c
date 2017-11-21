/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_rdfile_save_tetri.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:03:21 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/21 17:40:11 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../includes/libft/libft.h"
#include "sq_fillit.h"

void	ft_exit(char const *s)
{
	ft_putendl(s);
	exit(1);
}

void	only_dot_hash(char *s, int len)
{
	int		hash_count;
	int		index;

	hash_count = 0;
	index = 0;
	while (index < len)
	{
		if ((!((index + 1) % 5) || index == len -1))
		{
			if (s[index] && s[index]!= '\n')
				ft_exit("error");
		}
		else
		{
			if (s[index] != '.' && s[index] != '#')
				ft_exit("error");
			if (s[index] == '#')
				hash_count++;
		}
		index++;
	}
	if (hash_count != 4)
		ft_exit("error");
}

void	valid_tetri(char *s)
{
	int		touch_count;
	int		i;

	touch_count = 0;
	i = 0;
	while (i < BUFF_SIZE)
	{
		if (s[i] = '#')
		{
			if (i + 4 < BUFF_SIZE && s[i + 4] == '#')
				touch_count++;
			if (i != 3 && i != 8 && i != 13 && i != 18)
			{
				if (i + 1 < BUFF_SIZE && s[i+1] == '#')
					touch_count++;
			}
		}
	}
	if (touch_count != 3 && touch != 4)
		ft_exit("not valid file");
}

void  mv_left_top(char **s)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		test;

	x = 0;
	y = -1;
	while (!ft_strchr(s[x],'#')
			x++;
	while ( y < 4 && )
	{
		x = 0;
		while (x < 4 && s[x][y] != '#')
			x++;
		}
}


tetri_list	*add_tetri(unsigned short value, int nb, tetri_list *old_list)
{
	tetri_list	*list;
	tetri_list	*temp;

	if(!(list = (tetri_list *)malloc(sizeof(*list))))
		return (NULL);
	list->tetri_value = value;
	list->letter = 'A' + nb;
	list->length = 0;
	list->height = 0;
	list->next = NULL;
	mv_left_top_calcu(list);
	if(!old_list)
		old_list = list;
	else 
	{
		temp = old_list;
		while (temp->next)
			temp = temp->next;
		temp->next = list;
	}
	return (old_list);
}

tetri_list	*ft_readfile(char const *file_name)
{
	char				*buff;
	int				fd;
	unsigned	short	value_tetri;
	int				nb_tetri;
	tetri_list		*list;

	nb_tetri = 0;
	list = NULL;
	fd = open(file_name, O_RDONLY);
	if(fd == -1)
		ft_exit("error");
	if(!(buff = (char *)malloc(BUFF_SIZE)))
		return (NULL);
	while (read(fd, buff, BUFF_SIZE))
	{
		if (nb_tetri > 25)
			ft_exit("maxi tetri is 26");
		only_dot_hash(buff,BUFF_SIZE);
		value_tetri = tetri_value(buff, BUFF_SIZE);
		valid_tetri(value_tetri);
		list = add_tetri(value_tetri, nb_tetri, list);
		nb_tetri++;
		ft_bzero(buff, BUFF_SIZE);
	}
	return (list);
}

/*
   int	main(void)
   {
   char *s="....\n...#\n..##\n...#\n\n";
   only_dot_hash(s, 21);
   unsigned short t = tetri_value(s, 21);
   valid_tetri(t);
   int i = 15;
   while (i >= 0)
   {
   if (t & ( 1 << i))
   printf("1");
   else
   printf("0");
   i--;
   }
   printf("\n");
   t = mv_left_top(t);
   i = 15;
   while (i >= 0)
   {
   if (t & ( 1 << i))
   printf("1");
   else
   printf("0");
   i--;
   }
   }
   */

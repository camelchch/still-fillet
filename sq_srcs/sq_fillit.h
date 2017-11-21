/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq_fillit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 08:58:43 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/21 16:04:09 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FILLIT_H
#define	FILLIT_H

#define	BUFF_SIZE 21

typedef	struct	te_list
{
	char	**s;
	char	letter;
	struct	te_list	*next;
}				tetri_list;

void	ft_exit(char const *s);
tetri_list	*ft_readfile(char const *file_name);
void	print_tetri(unsigned short t);

#endif

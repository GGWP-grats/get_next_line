/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:47:24 by wquenten          #+#    #+#             */
/*   Updated: 2020/11/24 19:25:53 by wquenten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static size_t	size = 0;
	size_t			read;
	short			ret;
	char			buf[BUFF_SIZE]
	t_list			**start;
	
	if (fd < 0 || !line)
		return (0);
	while ((read = read(fd, buf, BUFF_SIZE)) > 0 )
	{
		ft_lstadd_front(start, buf);
		start->size = read;
	}
	return (ret);		
}

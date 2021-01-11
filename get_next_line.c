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


int                 find_endl(char *str, ssize_t size)
{   
    int             i;
   
    i = -1; 
	while ( ++i < size && str[i])
		if (str[i] == '\n')
			return (i);
	return (-1);  
}

char                *gnl_strdup(char *str, ssize_t size, char *func)
{
    char            *new_str;
    int             i;

    i = -1;
	//if (size == 1 && *str == '\n')
//		size--;
	//printf("\n(%s)ALLOC %zu FOR |%.*s|\n", func, size, (int)size, str);
	(void)*func;
    if (!str || size < 0 || !(new_str = malloc(sizeof(*new_str) * (size + 1))))
        return (NULL);
    while (++i <= size)
        new_str[i] = str[i];
    new_str[size] = '\0';
    return (new_str);
}

int                 read_line(int fd, char **line, t_rem *rm, t_head **lst_head)
{
	char			*buf;
	ssize_t 		size;
	ssize_t			endl;
	
	endl = -1;
	size = 0;
	while (endl == -1 && (buf = malloc(sizeof(*buf) * BUFFER_SIZE + 1)) &&
		  (size = read(fd, buf, BUFFER_SIZE)) > 0)
		if ((endl = find_endl(buf, size)) > -1)
			gnl_append_buff(lst_head, buf, endl);
		else if (endl == -1)
			gnl_append_buff(lst_head, buf, size);
	if (size <= 0)
		free(buf);	
	if (size > 0 && endl > -1 && ++endl < size && (rm->size = size - endl))
		if (!(rm->string = gnl_strdup(&buf[endl], size - endl, "create rm")))
			size = -1;
	if ((*lst_head)->overall_size > 0 && (size = 1))
		if (!(*line = gnl_concat(lst_head)))
			size = -1;
	if (size <= 0)
		if(!(*line = gnl_strdup("", 0, "zero lenght")))
			size = -1;
	gnl_clear(*lst_head, NULL, NULL);
	return (size);
}

int                 get_next_line(int fd, char **line)
{
    static t_rem    remainder;
    t_head          *lst_head;
    ssize_t         endl;
    char            *tmp;

    if (fd < 0 || !line || BUFFER_SIZE < 0 ||
            !(lst_head = malloc(sizeof(*lst_head))))
        return (-1);
    *lst_head = (t_head){NULL, NULL, 0};
    if (remainder.string && remainder.size > 0)
    {
       //printf("We have remainder <%s> size %zu\n", remainder.string, remainder.size);
       if ((endl = find_endl(remainder.string, remainder.size)) > -1)
       {
           if (!(*line = gnl_strdup(remainder.string, endl, "gnl")) && gnl_clear(lst_head, &remainder, NULL))
			   return (-1);
		   if (remainder.size -= endl + 1)
			   tmp = gnl_strdup(remainder.string + endl + 1, remainder.size, "recreate rm");
           gnl_clear(lst_head, &remainder, NULL); 
           remainder.string = tmp;
           return (1);
       }
       else if (!(gnl_append_buff(&lst_head, remainder.string, remainder.size)) || (remainder.string = NULL))
		   return (gnl_clear(lst_head, &remainder, NULL));
    }
    return (read_line(fd, line, &remainder, &lst_head));
}

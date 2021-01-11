/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:48:25 by wquenten          #+#    #+#             */
/*   Updated: 2020/11/24 18:41:01 by wquenten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1 
#endif
# define MAX_FD OPEN_MAX

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>//FIXME

typedef struct		s_rem
{
	char			*string;
	ssize_t			size;
}                   t_rem;

typedef struct		s_gnl
{
	char 		    *string;
	struct s_gnl	*next;
    ssize_t          size;
}				    t_gnl;

typedef struct      s_head
{
    t_gnl           *head;
    t_gnl           *tail;
    ssize_t          overall_size;
}                   t_head;

int 			    get_next_line(int fd, char **line);
int                 read_line(int fd, char **line, t_rem *rm, t_head **lst_head);
void 				*gnl_append_buff(t_head **head, char *str, ssize_t size);
char                *gnl_concat(t_head **head);
size_t              ft_strlcat(char *dst, const char *src, size_t dstsize);
char                *gnl_strdup(char *str, ssize_t size, char *func);
int                 find_endl(char *str, ssize_t size);
int                 gnl_clear(t_head *head, t_rem *remainder, char *buf);
    
#endif 

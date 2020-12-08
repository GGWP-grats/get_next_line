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
# define BUFFER_SIZE 1024
# define MAX_FD OPEN_MAX

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>//FIXME

typedef struct	    s_gnl
{
	char 		    string[BUFFER_SIZE + 1];
	struct s_gnl	*next;
    size_t          size;
}				    t_gnl;

typedef struct      s_head
{
    t_gnl           *head;
    t_gnl           *tail;
    size_t          overall_size;
}                   t_head;

int 			    get_next_line(int fd, char **line);
int                 gnl_read(int fd, char **line, t_head **head, static char *remainder);
int                 check_endl(char *buf);
int                 gnl_exit(char **line, char *buffer, t_head **head, static char *remainder);
void                gnl_append_buff(t_head **head, char *str, ssize_t size);
char                *gnl_concat(t_head **head);
size_t              ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t              ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif 

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

int     check_endl(char *buf)
{
    int i;
    
    i = -1;
    while (buf[++i])
        if (buf[i] == '\n')
            return (i);
    return (0);
}
int     gnl_read(int fd, char **line, t_head **head, static char *remainder)
{
    ssize_t     size;
    char        buff[BUFFER_SIZE + 1];
    int         endl;
    int         ret; 
    
    ret = 0;
    endl = 0;
    if (fd < 0 || BUFFER_SIZE < 1 || !line)
        return (-1);
    while ((size = read(fd, buff, BUFFER_SIZE)) > 0 && endl <= 1)
        if ((endl = check_endl(buff)) > 1)
        {
            gnl_append_buff(head, buff, endl + 1);
            ft_strlcpy(remainder, &buff[endl], size - endl);
            //remainder = &buff[endl];
            //*remainder++ = '\0';
            if (size - endl - 1 > 0)
                ret = 1;
        }
        else
            gnl_append_buff(head, buff, size + 1); 
    if (!(*line = gnl_concat(head)))
        return (gnl_exit(line, buff, NULL, remainder));
    return (ret);
}

int		get_next_line(int fd, char **line)
{
    t_head      *head;
    static char *remainder;
    int         endl;

    if (fd < 0 || !line || BUFFER_SIZE < 1)
        return (-1);
    if (!(head = malloc(sizeof(*head))))
        return (-1);
    endl = 0;
    if (remainder && *remainder){
        if ((endl = check_endl(remainder)))
        {
            printf("Found endl in remainder <%s> \n", remainder);
            gnl_append_buff(&head, remainder, endl + 1);
            remainder += endl + 1;
        }
        else
        {
            gnl_append_buff(&head, remainder, BUFFER_SIZE);
            remainder = NULL;
        }
    }
    return (gnl_read(fd, line, &head, remainder));
}

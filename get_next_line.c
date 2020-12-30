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

/*
 * This function cuts all \n in start of string and resize variable size
 * if \n cutted;
 * Then its allocates memory in heap and copy str in allocated memory
 * Returns new string;
*/
char                *gnl_strdup(char *str, ssize_t size)
{
    char            *new_str;
    int             i;

    i = - 1;
	if (size == 1 && *str == '\n')
		size--;
    if (!str || size < 0 || !(new_str = malloc(sizeof(*new_str) * (size + 1))))
        return (NULL);
    while (++i <= size)
        new_str[i] = str[i];
    new_str[size] = '\0';
    return (new_str);
}

/*
 * This is main funcution thats read in buff[BUFFER_SIZE]
 * the file stream fd. It's saves all read of stream in
 * linked list t_gnl via t_head saving read size. After endl 
 * occurience in file, adding all read buff before endl
 * and concatenate all list elem in **line;
 * If somethig read after \n copy all after it in 
 * t_rem static structure and assign its size
 * return:
 *  1 file not fully read
 *  0 met EOF
 * -1 error occured
*/
int                 read_line(int fd, char **line, t_rem *rm, t_head **lst_head)
{
    int             endl;
    char            *buff;
    int             ret;
    ssize_t         size;
    
	endl = -1;
	while (endl == -1 && (buff = malloc(sizeof(*buff) * BUFFER_SIZE)) 
		&& (size = read(fd, buff, BUFFER_SIZE)) > 0)  
	{	
		//printf("READ %zu <%s>\n", size, buff);
		if ((endl = find_endl(buff, size)) > 0)
            gnl_append_buff(lst_head, buff, endl);
        else if (endl == -1)
            gnl_append_buff(lst_head, buff, size);
	}
	if (size == BUFFER_SIZE)
		ret = 1;
	else if (size < BUFFER_SIZE)
		ret = 0;
	if ((*line = gnl_concat(lst_head)) == NULL || size < 0)
		return (gnl_clear(*lst_head, rm));
	if (*line != NULL && endl > 0 && (size - endl) > 0 
			&& (rm->string = gnl_strdup(&buff[size - endl], size - endl)))
		rm->size = size - endl;
	if (*line)
		gnl_clear(*lst_head, NULL);
	return (ret);
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
    if (remainder.string)
    {
//       printf("We have remainder <%s>\n", remainder.string);
       if ((endl = find_endl(remainder.string, remainder.size)) > 0)
       {
           *line = gnl_strdup(remainder.string, endl);
           remainder.size -= endl + 1;
           tmp = gnl_strdup(remainder.string + endl + 1, remainder.size);
           gnl_clear(lst_head, &remainder);  
           remainder.string = tmp;
           return (1);
       }
       else if (endl >= 0)
           gnl_append_buff(&lst_head, remainder.string,remainder.size);
    }
    return (read_line(fd, line, &remainder, &lst_head));
}

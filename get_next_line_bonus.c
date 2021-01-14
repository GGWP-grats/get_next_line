/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 02:34:52 by wquenten          #+#    #+#             */
/*   Updated: 2021/01/13 02:47:01 by wquenten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int					find_endl(char *str, ssize_t size)
{
	int				i;

	i = -1;
	while (++i < size && str[i])
		if (str[i] == '\n')
			return (i);
	return (-1);
}

char				*gnl_strdup(char *str, ssize_t size)
{
	char			*new_str;
	int				i;

	i = -1;
	if (!str || size < 0 || !(new_str = malloc(sizeof(*new_str) * (size + 1))))
		return (NULL);
	while (++i <= size)
		new_str[i] = str[i];
	new_str[size] = '\0';
	return (new_str);
}

int					rebuild_remainder(t_rem *remainder, int endl,
									char **line, t_head *lst_head)
{
	char			*tmp;

	if (!(*line = gnl_strdup(remainder->string, endl)))
		return (gnl_clear(lst_head, remainder, line, -1));
	if ((remainder->size -= endl + 1) < 0 ||
		!(tmp = gnl_strdup(&(remainder->string)[endl + 1], remainder->size)))
		return (gnl_clear(lst_head, remainder, line, -1));
	gnl_clear(lst_head, NULL, NULL, 0);
	free(remainder->string);
	remainder->string = tmp;
	return (1);
}

int					read_line(int fd, char **line, t_rem *rm, t_head **lst_head)
{
	char			*buf;
	ssize_t			size;
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
		if (!(rm->string = gnl_strdup(&buf[endl], size - endl)))
			size = -1;
	if ((*lst_head)->overall_size > 0 && size != -1
		&& ((*line = gnl_concat(lst_head))))
		return (size ? 1 : 0);
	else if (size != -1)
		return (gnl_clear(*lst_head, NULL, line, 0));
	else
		return (gnl_clear(*lst_head, rm, line, -1));
}

int					get_next_line(int fd, char **line)
{
	static t_rem	remainder[OPEN_MAX];
	t_head			*lst_head;
	ssize_t			endl;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 ||
			!(lst_head = malloc(sizeof(*lst_head))))
		return (-1);
	*lst_head = (t_head){NULL, NULL, 0};
	if (remainder[fd].string && remainder[fd].size > 0 &&
		(endl = find_endl(remainder[fd].string, remainder[fd].size)) > -1)
		return (rebuild_remainder(&remainder[fd], endl, line, lst_head));
	else if (remainder[fd].string &&
			(!(gnl_append_buff(&lst_head, remainder[fd].string,
			remainder[fd].size)) || (remainder[fd].string = NULL)))
		return (gnl_clear(lst_head, &remainder[fd], line, 0));
	return (read_line(fd, line, &remainder[fd], &lst_head));
}

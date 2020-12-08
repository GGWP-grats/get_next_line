#include "get_next_line.h"

void        gnl_append_buff(t_head **head, char *str, ssize_t size)
{
    t_gnl   *new;
    
    if (!(new = malloc(sizeof(*new))))
    {   
        printf("ERROR when trying allocate new list\n");
        return ;
    }
    new->next = NULL;
    ft_strlcpy(new->string, str, size);
    new->size = size;
    if (!(*head)->head)
    {
        (*head)->head = new;
        (*head)->tail = new;
        (*head)->overall_size = size;
    }
    else
    {
        (*head)->tail->next = new;
        (*head)->tail = new;
        (*head)->overall_size += size;
    }
    printf("Added list str<%s> size<%zu> overall_size<%zu>\n\n",(*head)->tail->string, (*head)->tail->size,\
            (*head)->overall_size);
}


char        *gnl_concat(t_head **head)
{
    size_t  all_size;
    t_gnl   *list;
    char    *line;

    all_size = (*head)->overall_size;
    if (all_size ==  0 || !head || !(*head)->head 
            || !(line = malloc(sizeof(*line)* (1 + all_size))) || !(*head)->head->string)
    {
        gnl_exit(&line, NULL, head, NULL);
        return (NULL);
    }
    list = (*head)->head;
    while (list)
    {
        ft_strlcat(line, list->string, list->size);
        list = list->next;
    }
    gnl_exit(NULL, NULL, head, NULL);
    return (line);
}

int        gnl_exit(char **line, char *buffer, t_head **head, static char *remainder)
{
    t_gnl   *list;
    
    if (buffer)
        buffer = NULL;
    if (remainder)
        remainder = NULL;
    if (head && (*head)->head)
        list = (*head)->head;
    if (line && *line && **line)
        free(*line);
    while (list)
    {
        (*head)->head = (*head)->head->next;
        free(list);
        list = (*head)->head;
    }
    if (head && *head)
        free(*head);
    return (-1);
}

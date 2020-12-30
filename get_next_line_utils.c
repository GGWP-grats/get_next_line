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
    new->string = gnl_strdup(str, size);
    new->size = size;
    if (!(*head)->overall_size)
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
    //printf("Added list str<%s> size<%zu> overall_size<%zu>\n\n",(*head)->tail->string, (*head)->tail->size,(*head)->overall_size);
}

char        *gnl_concat(t_head **head)
{
    int     all_size;
    t_gnl   *list;
    char    *str;
    int     i;
	int		k;

    all_size = (*head)->overall_size + 1;
    if (!(str = malloc(sizeof(*str) * all_size)))
        return (NULL);//FIXME free **head memory
    list = (*head)->head;
	k = 0;
    while (list && all_size)
    {   
        i = 0;
        while (i < list->size)
        {
           str[k++] = (list->string)[i++];
           all_size--;
        }
        list = list->next;    
    }
    str[(*head)->overall_size] = '\0';
    return (str);
}
int   gnl_clear(t_head *head, t_rem *remainder)
{
    t_gnl   *tmp;
    t_gnl   *list;

    if (remainder)
        free(remainder->string);
    if (head && head->head)
    {
		printf("\t\t\t\t\nxxxCLEAN LISTxxx\n");
        list = head->head;
        while (list)
        {
            tmp = list;
            list = list->next;
            free(tmp->string);
            free(tmp);
        }
    }
    if (head)
        free(head);
    return (-1);
}


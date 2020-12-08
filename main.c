#include "get_next_line.h"

int main (int ac, char **av)
{
    char    *line;
    int     fd = 0;
    
    if (ac > 1)
    {  
        fd = open(av[1], O_RDONLY);
        while (get_next_line(fd, &line) > 0)
        {
            printf("\ngnl returned |%s|\n", line);
            free(line);
        }
    
    }
    else
       while(get_next_line(0, &line) > 0)
       {
           printf("\ngnl returned |%s|\n", line);
           free(line);
       }
    printf("\nlast line gnl returned |%s|\n", line);
    free(line);
    return (0);
}

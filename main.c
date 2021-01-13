#include "get_next_line.h"
#include <stdio.h>

int main (int ac, char **av)
{
    char    *line;
    int     fd = 0;
    int     ret;

    if (ac > 1)
    {  
        fd = open(av[1], O_RDONLY);
        while ((ret = get_next_line(fd, &line)) > 0)
        {
            printf("\ngnl %d : |%s|\n", ret, line);
            free(line);
        }
    
    }
    else
       while((ret = get_next_line(0, &line)) > 0)
       {
           printf("\ngnl %d : |%s|\n", ret, line);
           free(line);
       }
    printf("\ngnl %d : |%s|\n", ret, line);
	if (line)
       free(line);
    return (0);
}

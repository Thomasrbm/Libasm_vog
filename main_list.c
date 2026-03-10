#include <stdio.h>
#include <stdlib.h>
#include "t_list.h"

int cmp(void *data, void *ref)
{
    return (*(int *)data - *(int *)ref);
}

void    print_list(t_list *begin)
{
    while (begin)
    {
        printf("%d -> ", *(int *)begin->data);
        begin = begin->next;
    }
    printf("NULL\n");
}

int main(void)
{
    t_list  *begin = NULL;
    int     a = 1, b = 2, c = 3, d = 2;

    ft_list_push_front(&begin, &a);
    ft_list_push_front(&begin, &b);
    ft_list_push_front(&begin, &c);

    printf("avant : ");
    print_list(begin);

    ft_list_remove_if(&begin, &d, cmp, free);       // le envoyer comme &begin et non begin  =  **

    printf("apres : ");
    print_list(begin);
    return (0);
}
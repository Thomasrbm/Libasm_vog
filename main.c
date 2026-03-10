#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>

typedef struct      s_list
{
    void            *data;
    struct s_list   *next;
}                   t_list;

int ft_read(int fd, char *buf, size_t count);
int ft_write(int fd, void *buf, size_t count);
char *ft_strcpy(char *s1, char *s2);
int ft_strcmp(char *s1, char *s2);
int ft_strlen(char *s1);
t_list  *ft_list_new(void *data);
void    ft_list_push_front(t_list **begin_list, void *data);
int	ft_atoi_base_utf32(char *string, char *base);
int ft_list_size(t_list *first);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
char *ft_strdup(char *str);


int main()
{
	int fd = open("to_read.txt", O_RDWR | O_CREAT | O_APPEND, 0644);

	ft_write(fd, "hello\n", 6);

	// printf("\n\nerrno = %d\n\n", errno);

	
	lseek(fd, 0, SEEK_SET);
	
	char *buff = malloc(100);
	int byte = ft_read(fd, buff, 100);
	printf("byte read = %d | content : \n%s\n", byte, buff);

	
	// printf("\n\nerrno = %d\n\n", errno);
	
	
	char *dest = malloc(100);
	char *src = "hello";
	ft_strcpy(dest, src);

	printf("\ncpy dest = %s\n", dest);

	int test = ft_strcmp(dest, src);
	printf("cmp = %d\n", test);

	printf("dest length = %d\n", ft_strlen(dest));


	printf("\n\nerrno = %d\n\n", errno);



	t_list *first_list = NULL;

	first_list = ft_list_new("1");
	ft_list_push_front(&first_list, "3");
	ft_list_push_front(&first_list, "0");
	ft_list_push_front(&first_list, "51");
	ft_list_push_front(&first_list, "2");
	ft_list_push_front(&first_list, "45");
    t_list *tmp = first_list;
    while (tmp)
    {
        printf("Content: %s\n", (char *)tmp->data);
        tmp = tmp->next;
    }

	
	printf("\nlist size : %d\n", ft_list_size(tmp));

	ft_list_sort(&first_list, ft_strcmp);
	tmp = first_list;
	while (tmp)
    {
        printf("Content: %s\n", (char *)tmp->data);
        tmp = tmp->next;
    }


    printf("\n\n\n ======= ERASE ========= \n\n\n");

	ft_list_remove_if(&first_list, "45", ft_strcmp, free);
	tmp = first_list;
	while (tmp)
    {
        printf("Content: %s\n", (char *)tmp->data);
        tmp = tmp->next;
    }


	return 0;
}


// gcc  main.c libasm.a
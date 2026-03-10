#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <errno.h>

#include <string.h>

extern ssize_t ft_read(int fd, void *buf, size_t count);

void test_read(ssize_t (*read_func)(int, void *, size_t), char *name)
{
    char    buf[10];
    ssize_t ret;

    printf("--- Test avec %s ---\n", name);
    
    errno = 0;
    ret = read_func(-1, buf, 10);
    
    printf("Valeur de retour : %zd\n", ret);
    if (ret < 0)
    {
        printf("Errno fixé à : %d\n", errno);
        printf("Message d'erreur : %s\n", strerror(errno));
    }
    printf("\n");
}

int main(void)
{
    test_read(read, "VRAI READ");

    test_read(ft_read, "FT_READ");

    return (0);
}
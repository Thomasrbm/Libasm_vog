#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <uchar.h>

typedef struct s_list {
    void          *data;
    struct s_list *next;
} t_list;

/* --- MANDATORY --- */
size_t  ft_strlen(const char *s);
char    *ft_strcpy(char *dest, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char    *ft_strdup(const char *s);

/* --- BONUS --- */
int     ft_atoi_base_utf32(const char32_t *str, const char32_t *base);
void    ft_list_push_front(t_list **begin_list, void *data);
int     ft_list_size(t_list *begin_list);
void    ft_list_sort(t_list **begin_list, int (*cmp)());
void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

void print_list(t_list *l) {
    while (l) {
        printf("[%s] -> ", (char *)l->data);
        l = l->next;
    }
    printf("NULL\n");
}

void dummy_free(void *p) { (void)p; }

int main() {
    char dest_ft[100], dest_lc[100];
    char buf_ft[100], buf_lc[100];
    ssize_t r_ft, r_lc;

    printf("===== MANDATORY PART COMPARISON =====\n\n");

    /* STRLEN */
    printf("[ft_strlen]\n");
    printf("  Long:  ft: %zu | libc: %zu\n", ft_strlen("Libasm is fun"), strlen("Libasm is fun"));
    printf("  Empty: ft: %zu | libc: %zu\n", ft_strlen(""), strlen(""));
    printf("  NULL:  ft: %zu\n", ft_strlen(NULL));

    /* STRCPY */
    printf("\n[ft_strcpy]\n");
    printf("  Normal:    ft: '%s' | libc: '%s'\n", ft_strcpy(dest_ft, "Hello"), strcpy(dest_lc, "Hello"));
    printf("  Empty:     ft: '%s' | libc: '%s'\n", ft_strcpy(dest_ft, ""), strcpy(dest_lc, ""));
    // Utilisation de %p pour ne pas dereferencer NULL
    printf("  SrcNULL:   ft: %p\n", ft_strcpy(dest_ft, NULL));
    printf("  DstNULL:   ft: %p\n", ft_strcpy(NULL, "test"));
    printf("  BothNULL:  ft: %p\n", ft_strcpy(NULL, NULL));

	// printf("  SrcNULL:   ft: %p | libc: %p\n", ft_strcpy(dest_ft, NULL), strcpy(dest_ft, NULL));
    // printf("  DstNULL:   ft: %p | libc: %p\n", ft_strcpy(NULL, "test"), strcpy(NULL, "test"));
    // printf("  BothNULL:  ft: %p | libc: %p\n", ft_strcpy(NULL, NULL), strcpy(NULL, NULL));

    /* STRCMP */
    printf("\n[ft_strcmp]\n");
    printf("  Same:       ft: %d | libc: %d\n", ft_strcmp("42", "42"), strcmp("42", "42"));
    printf("  Diff:       ft: %d | libc: %d\n", ft_strcmp("abc", "abd"), strcmp("abc", "abd"));
    printf("  S1 NULL:    ft: %d\n", ft_strcmp(NULL, "abc"));
    printf("  S2 NULL:    ft: %d\n", ft_strcmp("abc", NULL));
    printf("  Both NULL:  ft: %d\n", ft_strcmp(NULL, NULL));

    /* WRITE */
    printf("\n[ft_write & errno]\n");
    errno = 0; r_ft = ft_write(1, "  ft_write: OK\n", 15);
    int e_ft = errno;
    errno = 0; r_lc = write(1, "  libc_write: OK\n", 17);
    int e_lc = errno;
    printf("  Valid FD: ft_ret: %zd (err %d) | lc_ret: %zd (err %d)\n", r_ft, e_ft, r_lc, e_lc);
    
    errno = 0; r_ft = ft_write(-1, "err", 3);
    e_ft = errno;
    errno = 0; r_lc = write(-1, "err", 3);
    e_lc = errno;
    printf("  Bad FD:   ft_ret: %zd (err %d) | lc_ret: %zd (err %d)\n", r_ft, e_ft, r_lc, e_lc);

    /* READ */
    printf("\n[ft_read & errno]\n");
    int fd = open("test_cmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, "42 school", 9);
    lseek(fd, 0, SEEK_SET);
    r_ft = ft_read(fd, buf_ft, 9); if (r_ft >= 0) buf_ft[r_ft] = '\0';
    e_ft = errno;
    lseek(fd, 0, SEEK_SET);
    r_lc = read(fd, buf_lc, 9); if (r_lc >= 0) buf_lc[r_lc] = '\0';
    e_lc = errno;
    printf("  Content: ft: '%s' | lc: '%s'\n", buf_ft, buf_lc);
    printf("  Return:  ft: %zd (err %d) | lc: %zd (err %d)\n", r_ft, e_ft, r_lc, e_lc);
    close(fd); unlink("test_cmp.txt");

    /* STRDUP */
    printf("\n[ft_strdup]\n");
    char *s1 = ft_strdup("Gold"); char *s2 = strdup("Gold");
    printf("  Normal: ft: '%s' | libc: '%s'\n", s1, s2);
    free(s1); free(s2);
    s1 = ft_strdup(""); s2 = strdup("");
    printf("  Empty:  ft: '%s' | libc: '%s'\n", s1, s2);
    free(s1); free(s2);
    printf("  NULL:   ft: %p\n", ft_strdup(NULL));

    printf("\n===== BONUS PART (UTF-32) =====\n\n");

    /* ATOI BASE UTF-32 */
    printf("[ft_atoi_base_utf32]\n");
    printf("  Base 10 (U\"123\"): %d\n", ft_atoi_base_utf32(U"123", U"0123456789"));
    printf("  Base 2  (U\"101\"): %d\n", ft_atoi_base_utf32(U"101", U"01"));
    printf("  Base 16 (U\"ff\"):  %d\n", ft_atoi_base_utf32(U"ff", U"0123456789abcdef"));
    printf("  NULL Str:         %d\n", ft_atoi_base_utf32(NULL, U"01"));
    printf("  NULL Base:        %d\n", ft_atoi_base_utf32(U"123", NULL));

    /* LISTS */
    printf("\n[List Operations]\n");
    t_list *list = NULL;
    ft_list_push_front(&list, "Paris");
    ft_list_push_front(&list, "Lyon");
    ft_list_push_front(&list, "Marseille");
    
    printf("  Size: %d\n", ft_list_size(list));
    printf("  Before sort: "); print_list(list);
    ft_list_sort(&list, (int (*)())ft_strcmp);
    printf("  After sort:  "); print_list(list);
    
    ft_list_remove_if(&list, "Lyon", (int (*)())ft_strcmp, dummy_free);
    printf("  After rm Lyon: "); print_list(list);

    /* Cleanup */
    while (list) { t_list *n = list->next; free(list); list = n; }

    return 0;
}
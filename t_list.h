// t_list.h
#ifndef T_LIST_H
# define T_LIST_H

typedef struct	s_list
{
	void		*data;
	struct s_list	*next;
}	t_list;

t_list	*ft_list_new(void *data);
void    ft_list_push_front(t_list **begin, void *data);
void	ft_list_remove_if(t_list **begin, void *data_ref, int (*cmp)(void *, void *), void (*free_fct)(void *));

#endif
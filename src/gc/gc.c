#include "cub3d.h"

static t_malloc	**get_gc(void)
{
	static t_malloc	*g_mallocs = NULL;
	return (&g_mallocs);
}

void	*ft_malloc(size_t size)
{
	void		*ptr;
	t_malloc	*new;
	t_malloc	**gc;

	gc = get_gc();
	ptr = malloc(size);
	if (!ptr)
		ft_gc_exit(EXIT_FAILURE);
	new = malloc(sizeof(t_malloc));
	if (!new)
	{
		free(ptr);
		ft_gc_exit(EXIT_FAILURE);
	}
	new->ptr = ptr;
	new->next = *gc;
	*gc = new;
	return (ptr);
}

void	ft_free(void *ptr)
{
	t_malloc	**gc;
	t_malloc	*curr;
	t_malloc	*prev;

	if (!ptr)
		return;
	gc = get_gc();
	curr = *gc;
	prev = NULL;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				*gc = curr->next;
			free(curr->ptr);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_gc_free_all(void)
{
	t_malloc	**gc;
	t_malloc	*curr;
	t_malloc	*tmp;

	gc = get_gc();
	curr = *gc;
	while (curr)
	{
		tmp = curr->next;
		free(curr->ptr);
		free(curr);
		curr = tmp;
	}
	*gc = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


void	ft_gc_exit(int status)
{
	ft_gc_free_all();
	exit(status);
}
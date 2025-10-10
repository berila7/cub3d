/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anachat <anachat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:01:58 by anachat           #+#    #+#             */
/*   Updated: 2025/10/10 18:11:59 by anachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gcnode	**get_gc(void)
{
	static t_gcnode	*gc;

	return (&gc);
}

void	gc_free(void *ptr)
{
	t_gcnode	**gc;
	t_gcnode	*curr;
	t_gcnode	*prev;

	gc = get_gc();
	if (!gc || !*gc)
		return ;
	(1) && (curr = *gc, prev = NULL);
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				*gc = curr->next;
			if (curr->ptr)
				free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_all(void)
{
	t_gcnode	*curr;
	t_gcnode	*next;
	t_gcnode	**gc;

	gc = get_gc();
	if (!gc || !*gc)
		return ;
	curr = *gc;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
		{
			free(curr->ptr);
			curr->ptr = NULL;
		}
		free(curr);
		curr = next;
	}
	*gc = NULL;
}

static void	append_gc(t_gcnode **gc, void *ptr)
{
	t_gcnode	*node;
	t_gcnode	*last;

	node = gc_malloc(sizeof(t_gcnode));
	if (!node)
	{
		write(2, "Allocation Error\n", ft_strlen("Allocation Error\n"));
		gc_free_all();
		exit(1);
	}
	node->ptr = ptr;
	node->next = NULL;
	if (!*gc)
		*gc = node;
	else
	{
		last = *gc;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Allocation Error\n", ft_strlen("Allocation Error\n"));
		gc_free_all();
		exit(1);
	}
	ft_bzero(ptr, size);
	append_gc(get_gc(), ptr);
	return (ptr);
}

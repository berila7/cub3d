/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberila <mberila@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:01:58 by anachat           #+#    #+#             */
/*   Updated: 2025/07/28 17:36:52 by mberila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_gcnode *gc = NULL;

static t_gcnode **get_gc(void)
{
    return (&gc);
}

void	gc_free(t_gcnode **gc, void *ptr)
{
	t_gcnode	*curr;
	t_gcnode	*prev;

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
			if (curr->ptr)
				free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	free(ptr);
}

void	gc_free_all(void)
{
	t_gcnode	*curr;
	t_gcnode	*next;

	if (!gc)
		return ;
	curr = gc;
	while (curr)
	{
		next = curr->next;
		if (curr->ptr)
			free(curr->ptr);
		free(curr);
		curr = next;
	}
	gc = NULL;
}

static void	append_gc(t_gcnode **gc, void *ptr)
{
	t_gcnode	*node;
	t_gcnode	*last;

	node = malloc(sizeof(t_gcnode));
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

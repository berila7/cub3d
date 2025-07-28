#include "cub3d.h"

t_texture	*new_txt(char *direction, char *path, int fd)
{
	t_texture	*texture;

	texture = gc_malloc(sizeof(t_texture) + 1);
	if (!texture)
		return (NULL);
	texture->fd = fd;
	texture->direction = gc_strdup(direction);
	if (!texture->direction)
	{
		close(fd);
		return (NULL);
	}
	texture->path = gc_strdup(path);
	if (!texture->path)
	{
		close(fd);
		return (NULL);
	}
	texture->next = NULL;
	return (texture);
}

void	add_txt(t_texture **texutre, t_texture *new_texutre)
{
	t_texture	*current;

	if (!new_texutre)
		return ;
	if (!*texutre)
	{
		*texutre = new_texutre;
		return ;
	}
	current = *texutre;
	while (current->next)
		current = current->next;
	current->next = new_texutre;
}

#include "cub3d.h"

t_texture	*new_txt(char *direction, char *path)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture) + 1);
	if (!texture)
		return (NULL);
	texture->direction = ft_strdup(direction);
	if (!texture->direction)
	{
		free(texture);
		return (NULL);
	}
	texture->path = ft_strdup(path);
	if (!texture->path)
	{
		free(texture->direction);
		free(texture);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:50:13 by ael-garr          #+#    #+#             */
/*   Updated: 2024/10/17 19:10:10 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	herdoc_open(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

char	*herdoc_reading(int fd)
{
	char	*buffer;
	char	*result;
	ssize_t	readed;

	readed = read(fd, buffer,sizeof(ssize_t));
	if(readed)
	{
		result = ft_strdup(buffer);
		if(!result)
			return (NULL);
	}
	return (result);
}
char	*herdoc(char *file_name, int fd)
{
	int file_des;
	char	*result;
	
	file_des = herdoc_open(file_name);
	if (fd < 0)
		return (NULL);
	result = herdoc_reading(fd);
	if (!result)
		return (NULL);
	return(result);
}
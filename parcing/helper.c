/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:42:59 by yosabir           #+#    #+#             */
/*   Updated: 2024/10/23 09:43:31 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (len == 0 || (size_t)start >= (size_t)ft_strlen(s))
		return (ft_strdup(""));
	if (len < ft_strlen(s) - start)
		ptr = malloc(len + 1);
	else
		ptr = malloc(ft_strlen(s) - start + 1);
	if (!ptr)
		return (NULL);
	while ((size_t)i < len && s[start + i] != '\0')
	{
		ptr[i] = s[i + start];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
		write(fd, &c, 1);
}

int error_message()
{
	printf("syntax error \n");
	exit_status(258, 1);
	return (-1);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len1);
	ft_memcpy(ptr + len1, s2, len2);
	ptr[len1 + len2] = '\0';
	return (ptr);
}

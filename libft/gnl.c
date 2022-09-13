/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:16:16 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/12 14:45:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_that_line(char *patch)
{
	int		i;
	char	*str;

	str = ft_mallocable(patch);
	if (!str)
		return (NULL);
	i = 0;
	while (patch[i] && patch[i] != '\n')
	{
		str[i] = patch[i];
		i++;
	}
	if (patch[i] == '\n')
	{
		str[i] = patch[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_patch(char *patch)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (patch[i] && patch[i] != '\n')
		i++;
	if (!patch[i])
	{
		free(patch);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen_gnl(patch) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (patch[i])
		str[j++] = patch[i++];
	str[j] = '\0';
	free(patch);
	return (str);
}

char	*ft_strjoin_gnl(char *patch, char *buf)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!patch)
	{
		patch = malloc(sizeof(char) * 1);
		patch[0] = '\0';
	}
	if (!patch || !buf)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen_gnl(patch)
					+ ft_strlen_gnl(buf)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (patch)
		while (patch[++i] != '\0')
			str[i] = patch[i];
	while (buf[j] != '\0')
		str[i++] = buf[j++];
	str[i] = '\0';
	free(patch);
	return (str);
}

char	*ft_feed_patch(int fd, char *patch)
{
	char	buf[BUFFER_SIZE + 1];
	int		end;

	end = 1;
	while (!ft_strchr_gnl(patch, '\n') && end != 0)
	{
		end = read(fd, buf, BUFFER_SIZE);
		if (end == -1)
			return (NULL);
		buf[end] = '\0';
		patch = ft_strjoin_gnl(patch, buf);
	}
	return (patch);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*patch[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	patch[fd] = ft_feed_patch(fd, patch[fd]);
	if (!patch[fd])
		return (NULL);
	line = ft_get_that_line(patch[fd]);
	patch[fd] = ft_new_patch(patch[fd]);
	return (line);
}

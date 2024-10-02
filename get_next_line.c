/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:19:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/30 09:19:48 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*new_stash(char *stash)
{
	int		len;
	char	*nstash;
	char	*ptr;

	ptr = ft_strchr(stash, '\n');
	if (!ptr)
	{
		nstash = NULL;
		return (ft_free(&stash));
	}
	else
		len = (ptr - stash) + 1;
	if (!stash[len])
		return (ft_free(&stash));
	nstash = ft_substr(stash, len, ft_strlen(stash) - len);
	ft_free(&stash);
	if (!nstash)
		return (NULL);
	return (nstash);
}

char	*make_line(char *stash)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(stash, '\n');
	len = (ptr - stash) + 1;
	line = ft_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_buf(int fd, char *stash)
{
	int		rb;
	char	*buffer;

	rb = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || BUFFER_SIZE < 1)
		return (ft_free(&stash));
	buffer[0] = '\0';
	while (rb > 0 && !ft_strchr(buffer, '\n'))
	{
		rb = read(fd, buffer, BUFFER_SIZE);
		if (rb > 0)
		{
			buffer[rb] = '\0';
			stash = ft_strjoin(stash, buffer);
		}
	}
	free(buffer);
	if (rb == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if ((stash && !ft_strchr(stash, '\n')) || !stash)
		stash = read_buf(fd, stash);
	if (!stash)
		return (NULL);
	line = make_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = new_stash(stash);
	return (line);
}

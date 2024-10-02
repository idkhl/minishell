/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:54:33 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 15:27:35 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*extract_line(char *all_read)
{
	int		i;
	int		line_length;
	char	*line;

	i = 0;
	line_length = 0;
	while (all_read[line_length] && all_read[line_length] != '\n')
	{
		line_length++;
	}
	if (all_read[line_length] == '\n')
		line_length++;
	line = malloc((line_length + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_length)
	{
		line[i] = all_read[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	clean_read_line(char **all_read)
{
	int		i;
	int		j;
	char	*temp;

	j = 0;
	while ((*all_read)[j] && (*all_read)[j] != '\n')
		j++;
	if ((*all_read)[j] == '\n')
		j++;
	temp = malloc((ft_strlen(*all_read) - j + 1) * sizeof(char));
	if (!temp)
		return ;
	i = 0;
	while ((*all_read)[j])
		temp[i++] = (*all_read)[j++];
	temp[i] = '\0';
	free(*all_read);
	*all_read = temp;
}

void	new_all_read(char **all_read, char *buffer, int nb_bytes_read)
{
	char	*temp;
	int		all_read_length;

	all_read_length = 0;
	if (*all_read)
		all_read_length = ft_strlen(*all_read);
	temp = malloc((all_read_length + nb_bytes_read + 1) * sizeof(char));
	if (!temp)
		return ;
	if (*all_read)
		ft_strcpy(temp, *all_read);
	ft_strncat(temp, buffer, nb_bytes_read);
	free(*all_read);
	*all_read = temp;
}

void	read_and_add(int fd, char **all_read)
{
	char		*buffer;
	int			nb_bytes_read;

	nb_bytes_read = 1;
	while (!found_newlines(*all_read) && nb_bytes_read > 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		nb_bytes_read = (int)read(fd, buffer, BUFFER_SIZE);
		if ((!(*all_read) && nb_bytes_read == 0) || nb_bytes_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[nb_bytes_read] = '\0';
		if (!(*all_read))
			(*all_read) = ft_strdup("");
		if (!(*all_read))
			return ;
		new_all_read(all_read, buffer, nb_bytes_read);
		free(buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*all_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	read_and_add(fd, &all_read);
	if (!all_read)
		return (NULL);
	line = extract_line(all_read);
	clean_read_line(&all_read);
	if (all_read && *all_read == '\0')
	{
		free(all_read);
		all_read = NULL;
	}
	return (line);
}

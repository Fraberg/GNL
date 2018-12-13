/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 00:37:59 by fberger           #+#    #+#             */
/*   Updated: 2018/12/01 20:01:38 by fberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int split_nl(char **str, char **line, char *to_split)
{
	int len;
	//char *tmp;

	len = ft_strchr(to_split, '\n') - to_split + 1;
	//tmp = ft_strdup(to_split);
	//(to_split ? free(to_split) : "");
	*line = ft_strsub(to_split, 0, len - 1);
	*str = ft_strsub(to_split, len, ft_strlen(to_split) - len);
	//(tmp ? free(tmp) : "");
	return (1);
}

static int cp_str_in_line(char **str, char **line)
{
	//char *tmp;

	if (ft_strchr(*str, '\n') && split_nl(str, line, *str))
		return (1);
	//tmp = ft_strdup(*line);
	//(*line ? free(*line) : "");
	*line = ft_strjoin(*str, *line);
	//(tmp ? free(tmp) : "");
	//*str = NULL;
	ft_strdel(str);
	return (0);
}

static int reach_NLorEOF(int fd, char *buf, char **line, char **str)
{
	int ret;
	char	prev;

	prev = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) >= 1 || *str)
	{
		if (ret > 0) // ok
			prev = ret;
		if (ret == 0) // si EOF, renvoyer 1 une dernière fois si str
		{
			if (*str != NULL && cp_str_in_line(str, line) >= 0)
					return (1); // si EOF mais il reste qqchose a retourner
			return (0); // si EOF + il reste rien a retourner
		}
		buf[ret] = '\0';
		*line = ft_strjoin(*line, buf);
  	if (ft_strchr(*line, '\n') && split_nl(str, line, *line)) // splitter si line contient un /n
				return (ret);
	}
	if (ret == -1) // ok
				return (-1);
	if (ret < prev) // EOF pendant le while
		return (1);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[10000] = {NULL};
	char		*buf;
	int			ret;

	if (!line || fd < 0 || BUFF_SIZE < 1 || !(*line = ft_strnew(BUFF_SIZE)))
			return (-1);
	if (str[fd] && cp_str_in_line(&str[fd], line))
		return (1);
	buf = ft_strnew(BUFF_SIZE);
	ret = reach_NLorEOF(fd, buf, line, &str[fd]);
  ft_strdel(&buf);
	if (ret == -1)
	{
			return (-1);
	}
	if (ret == 0 && !str[fd])
	{
			return (0);
	}
	return (1);
}

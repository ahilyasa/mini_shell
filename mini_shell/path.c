/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:40:51 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 08:15:05 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

char	*path_finder(char *s)
{
	char	*si;

	si = calloc (sizeof(char), strlen(s));
	getcwd(si, strlen(s));
	printf("%s\n", si);
	return (si);
}

int	check_abs(char *path)
{
	return (checkacces(path));
}

static int	check_in_path(char **line, char *path, char **theway)
{
	int		i;
	char	*old;
	char	*temp;

	i = 0;
	while (line[i])
	{
		old = ft_strjoin(line[i], "/");
		temp = ft_strjoin(old, path);
		free(old);
		if (checkacces(temp))
		{
			*theway = temp;
			free(line);
			return (1);
		}
		i++;
	}
	error_exit(127, path, "command not found");
	return (0);
}

int	get_path(char *path, char **theway)
{
	char	**line;
	char	*temp;

	temp = find_envpath(g_stuff->env);
	line = ft_split(temp, ':');
	free(temp);
	if (is_in(path, '/') && check_abs(path))
	{
		*theway = path;
		free(line);
		return (1);
	}
	else if (is_in(path, '/'))
		error_exit(127, path, "No such a file or directory");
	if (check_in_path(line, path, theway))
		return (1);
	return (0);
}

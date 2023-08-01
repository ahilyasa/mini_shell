/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:39:11 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 06:29:04 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	delim_wr(int *pipes, char *buffer, t_parsed *parsed)
{
	(void)parsed;
	pipe(pipes);
	write(pipes[1], buffer, ft_strlen(buffer));
	dup2(pipes[0], 0);
	close(pipes[1]);
}

void	tmp_next(t_redir **tmp, char **key)
{
	while (*tmp)
	{
		if (!ft_strncmp((*tmp)->type, "<<", 2))
		{
			*key = (*tmp)->file;
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
}

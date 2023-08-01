/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparses.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:19:57 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 09:02:15 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	ff_re(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
}

int	is_token(char *token)
{
	char	*tokens;
	char	**tokenlist;
	int		i;

	if (!token)
		return (0);
	tokens = "| > >> < <<";
	tokenlist = ft_split(tokens, ' ');
	i = 0;
	while (tokenlist[i])
	{
		if (!strcmp_abs(token, tokenlist[i]))
		{
			ff_re(tokenlist);
			free(tokenlist);
			if (i == 0)
				return (2);
			return (1);
		}
		i++;
	}
	ff_re(tokenlist);
	free(tokenlist);
	return (0);
}

int	iterate_till(char *str, int start, int c)
{
	while (str && str[start] && str[start] != c)
		start++;
	return (start);
}

char	*put_expand(char *str, int index)
{
	char	*rtn;
	int		i;
	int		j;

	rtn = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	i = -1;
	while (++i <= index)
		rtn[i] = str[i];
	rtn[i] = ' ';
	j = i;
	i++;
	while (str[j])
	{
		rtn[i] = str[j];
		i++;
		j++;
	}
	return (rtn);
}

void	change_it(char **arg, int *i, int index)
{
	char	*temp;

	temp = *arg;
	*arg = put_expand(*arg, index);
	*i = 0;
	free(temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparses3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:20:22 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 09:19:40 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	redo_first(char **arg)
{
	char	*temp;

	temp = *arg;
	*arg = redo(*arg);
}

int	find_next_one(char *arg, int i)
{
	i++;
	if (ft_isdigit(arg[i]))
		return (i);
	while (arg[i] && (ft_isalpha(arg[i]) || \
	ft_isdigit(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

static void	next_o(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != 39)
		(*i)++;
}

void	next_next(char *arg, int *i)
{
	int	last;

	(*i)++;
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
		{
			last = find_next_one(arg, *i);
			ft_memmove(&arg[*i], &arg[last], \
			ft_strlen(&arg[last]) + 1);
			continue ;
		}
		(*i)++;
	}
}

void	fix_env_var(char **arg)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	while (arg[0][i])
	{
		if (arg[0][i] == '$')
		{
			last = find_next_one(arg[0], i);
			ft_memmove(&arg[0][i], &arg[0][last], ft_strlen(&arg[0][last]) + 1);
			continue ;
		}
		if (arg[0][i] == '"')
			next_next(&arg[0][i], &i);
		if (arg[0][i] == 39)
			next_o(arg[0], &i);
		i++;
	}
}

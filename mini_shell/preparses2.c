/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparses2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:20:11 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 09:01:46 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	is_token_char(int c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '|')
		return (2);
	return (0);
}

int	check_tokens(char **lst)
{
	int	i;
	int	temp;

	i = 0;
	while (lst[i])
	{
		if (is_token_char(lst[i][0]) && !is_token(lst[i]))
			return (0);
		if (is_token(lst[i]) && !lst[i + 1])
			return (0);
		temp = is_token(lst[i]);
		if (temp != 2 && temp && is_token(lst[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	findindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

void	fix_quote(char **lst, int j)
{
	int	i;

	i = -1;
	while (lst[++i])
	{
		j = 0;
		while (lst[i][j] && !is_token(lst[i]))
		{
			if (lst[i][j] == '"')
			{
				ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
				j += findindex(&lst[i][j], '"');
				ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
				continue ;
			}
			if (lst[i][j] == 39)
			{
				ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
				j += findindex(&lst[i][j], 39);
				ft_memmove(&lst[i][j], &lst[i][j + 1], ft_strlen(&lst[i][j]));
				continue ;
			}
			j++;
		}
	}
}

char	**pre_parse(char *str)
{
	char	*arg;
	char	**pre_parsed;

	arg = removespace(str, 0);
	if (!arg)
		return (0);
	pre_parsed = specialsplit(arg, ' ');
	free(arg);
	if (!check_tokens(pre_parsed))
	{
		print_error("minishell", " ", "syntax error2!");
		ft_myexport(ft_itoa(258));
		return (0);
	}
	return (pre_parsed);
}

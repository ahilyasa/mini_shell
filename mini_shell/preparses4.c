/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparses4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 07:20:34 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 11:19:00 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

int	getin(int ac)
{
	char	*c;
	char	**preparsed;

	(void)ac;
	c = readline("MimiShell $> ");
	if (c && *c)
	{
		iss_to_s(c);
		preparsed = pre_parse(c);
		if (!preparsed)
			return (1);
		doit2(preparsed);
		add_history(c);
	}
	if (!c)
		return (0);
	free(c);
	return (1);
}

void	error_on(void)
{
	print_error("minishell", " ", "quote error");
	ft_myexport(ft_itoa(258));
}

static void	next_of(char *arg, int *i, char c)
{
	(*i)++;
	while (arg[*i] && arg[*i] != c)
		(*i)++;
	(*i)++;
}

char	*redo(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
		{
			next_of(arg, &i, '"');
			continue ;
		}
		if (arg[i] == 39)
		{
			next_of(arg, &i, 39);
			continue ;
		}
		if (i > 0 && is_token_char(arg[i]) && (!is_token_char(arg[i - 1]) \
		|| arg[i - 1] == '|') && arg[i - 1] != ' ')
			change_it(&arg, &i, i - 1);
		else if (arg[i] && is_token_char(arg[i]) && (!is_token_char(arg[i + 1]) \
		|| arg[i + 1] == '|') && arg[i + 1] != ' ')
			change_it(&arg, &i, i);
		else
			i++;
	}
	return (arg);
}

char	*removespace(char *str, int i)
{
	char	*arg;

	arg = ft_strdup(str);
	if (!pre_control(arg, ft_strlen(arg)))
	{
		error_on();
		return (0);
	}
	fit_env_var(&arg);
	fix_env_var(&arg);
	while (arg[i])
	{
		if (ft_isspace(arg[i]))
			cut_spaces(&arg, i + 1);
		if (arg[i] == '"')
		{
			i++;
			i = iterate_till(arg, i, '"');
		}
		if (arg[i] == '\'')
			i = iterate_till(arg, ++i, '\'');
		i += (arg[i] != 0);
	}
	redo_first(&arg);
	return (arg);
}

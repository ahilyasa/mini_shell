/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyarikan <iyarikan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:42:11 by ialgac            #+#    #+#             */
/*   Updated: 2022/09/28 11:13:50 by iyarikan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"

void	sig_handler(int signum)
{	
	if (signum == SIGINT)
	{
		printf("\n");
		if (!g_stuff->forks)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		rl_redisplay();
	}	
}

int	go(int ac, char **av)
{
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (getin(ac))
	{
		(void)0;
	}
	return (1);
}

char	**putmenv(char **env)
{
	char	**rtn;
	int		len;
	int		i;

	i = -1;
	len = lenof(env);
	rtn = malloc((len + 1) * sizeof(char *));
	while (++i < len)
		rtn[i] = ft_strdup(env[i]);
	rtn[i] = 0;
	return (rtn);
}

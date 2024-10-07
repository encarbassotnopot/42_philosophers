/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/07 15:53:28 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	necromancer(t_winfo *w)
{
	int				i;
	int				ate_enough;
	int				body_count;
	struct timeval	tv;

	body_count = 0;
	while (1)
	{
		i = -1;
		ate_enough = 1;
		while (++i < w->params[PHILS] && !body_count && ate_enough)
		{
			gettimeofday(&tv, NULL);
			pthread_mutex_lock(&w->ph_muts[i]);
			if (w->phinfos[i].ate < w->params[MEALS] && w->params[MEALS])
				ate_enough = 0;
			if (time_diff(&w->phinfos[i].last_meal, &tv) / 1000 > w->params[TTDIE])
			{
				print_msg(&w->phinfos[i], "died");
				body_count++;
			}
			pthread_mutex_unlock(&w->ph_muts[i]);
		}
		if ((ate_enough && w->params[MEALS]) || body_count)
		{
			pthread_mutex_lock(&w->sim_mut);
			w->sim_status = DEAD;
			pthread_mutex_unlock(&w->sim_mut);
			break ;
		}
	}
	dprintf(STDERR_FILENO, "necro dead \n");
}

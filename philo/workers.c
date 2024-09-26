/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/26 18:40:18 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	necromancer(t_winfo *w)
{
	int				i;
	int				ate_enough;
	int				body_count;
	struct timeval	meal_limit;

	body_count = 0;
	while (1)
	{
		gettimeofday(&meal_limit, NULL);
		time_subt(&meal_limit, w->params[TTDIE]);
		i = -1;
		ate_enough = 1;
		while (++i < w->params[PHILS] && body_count == 0)
		{
			pthread_mutex_lock(&w->ph_muts[i]);
			if (w->phinfos[i].ate < w->params[MEALS] && w->params[MEALS])
				ate_enough = 0;
			if (time_diff(&w->phinfos[i].last_meal, &meal_limit) == -1)
			{
				print_msg(&w->phinfos[i], "died");
				body_count++;
			}
			pthread_mutex_unlock(&w->ph_muts[i]);
		}
		if (ate_enough == w->params[PHILS] || body_count > 0)
		{
			pthread_mutex_lock(&w->sim_mut);
			w->sim_status = DEAD;
			pthread_mutex_unlock(&w->sim_mut);
			break ;
		}
	}
}

void	waiter(t_winfo *w)
{
	int	i;
	int	finished_eating;
	int	meal_count;
	int	meal_min;

	meal_count = 0;
	while (w->sim_status == ALIVE)
	{
		i = -1;
		finished_eating = 1;
		meal_min = w->phinfos[0].ate;
		while (++i < w->params[PHILS])
		{
			if (w->phinfos[i].ate < meal_min)
			{
				meal_min = w->phinfos[i].ate;
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/08 12:01:05 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	welfare_check(t_winfo *w, int i, int *body_count, int *ate_enough)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&w->ph_muts[i]);
	if (w->phinfos[i].ate < w->params[MEALS] && w->params[MEALS])
		*ate_enough = 0;
	if (time_diff(&w->phinfos[i].last_meal, &tv) / 1000 > w->params[TTDIE]
		&& w->phinfos[i].last_meal.tv_sec != 0)
	{
		print_msg(&w->phinfos[i], "died");
		*body_count += 1;
	}
	pthread_mutex_unlock(&w->ph_muts[i]);
}

void	necromancer(t_winfo *w)
{
	int	i;
	int	ate_enough;
	int	body_count;

	body_count = 0;
	while (1)
	{
		i = -1;
		ate_enough = 1;
		while (++i < w->params[PHILS] && !body_count && ate_enough)
			welfare_check(w, i, &body_count, &ate_enough);
		if ((ate_enough && w->params[MEALS]) || body_count)
		{
			pthread_mutex_lock(&w->sim_mut);
			w->sim_status = DEAD;
			pthread_mutex_unlock(&w->sim_mut);
			break ;
		}
	}
}

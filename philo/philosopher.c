/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/20 13:21:31 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_forks(t_phinfo *info)
{
	while (1)
	{
		pthread_mutex_unlock(&info->forks[(id - 1 + count) % count]);
	}
}

void	next_task(t_phinfo *info, int id, int count)
{
	if (info->ph_status == THINKING)
	{
		wait_forks(info);
		pthread_mutex_lock(&info->forks[(id - 1 + count) % count]);
		print_msg(info, "has taken a fork");
		pthread_mutex_lock(&info->forks[(id + 1) % count]);
		print_msg(info, "has taken a fork");
		info->ph_status = EATING;
		gettimeofday(&info->last_meal, NULL);
		info->may_eat = 0;
		info->ate++;
		print_msg(info, "is eating");
		pthread_mutex_unlock(&info->forks[(id - 1 + count) % count]);
		pthread_mutex_unlock(&info->forks[(id + 1) % count]);
		usleep(info->params[TTEAT] * 1000);
	}
	else if (info->ph_status == EATING)
	{
		info->ph_status = SLEEPING;
		print_msg(info, "is sleeping");
		usleep(info->params[TTEEP] * 1000);
	}
	else if (info->ph_status == SLEEPING)
	{
		info->ph_status = THINKING;
		print_msg(info, "is thinking");
	}
}

void	philosophate(t_phinfo *info)
{
	if (info->last_meal.tv_sec == 0)
		gettimeofday(&info->last_meal, NULL);
	if (info->ph_id % 2 == 0)
		info->may_eat = 1;
	else
		info->may_eat = 0;
	while (*info->sim_status == ALIVE)
	{
		pthread_mutex_lock(info->ph_mut);
		next_task(info, info->ph_id, info->params[PHILS]);
		pthread_mutex_unlock(info->ph_mut);
	}
}

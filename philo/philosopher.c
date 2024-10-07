/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/07 15:07:11 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_sim_status(t_phinfo *info)
{
	int	status;

	pthread_mutex_lock(info->sim_mut);
	status = *info->sim_status;
	pthread_mutex_unlock(info->sim_mut);
	return (status);
}

void	isleep(t_phinfo *info, int ms)
{
	struct timeval	alarm;
	struct timeval	current_time;

	gettimeofday(&alarm, NULL);
	time_add(&alarm, ms);
	gettimeofday(&current_time, NULL);
	pthread_mutex_unlock(info->ph_mut);
	while (time_diff(&current_time, &alarm) > 0
		&& get_sim_status(info) == ALIVE)
	{
		usleep(1000);
		gettimeofday(&current_time, NULL);
	}
	pthread_mutex_lock(info->ph_mut);
}

void	eat(t_phinfo *info, int id, int count)
{
	while (1)
	{
		pthread_mutex_lock(info->eat_mut);
		if (*info->may_eat > 0)
		{
			*info->may_eat -= 1;
			break ;
		}
		pthread_mutex_unlock(info->eat_mut);
		if (get_sim_status(info) != ALIVE)
			return ;
	}
	pthread_mutex_unlock(info->eat_mut);
	pthread_mutex_lock(info->forks + id);
	print_msg(info, "has taken a fork");
	pthread_mutex_lock(info->forks + (id + 1) % count);
	print_msg(info, "has taken a fork");
	info->ph_status = EATING;
	gettimeofday(&info->last_meal, NULL);
	info->ate++;
	pthread_mutex_unlock(info->forks + id);
	pthread_mutex_unlock(info->forks + (id + 1) % count);
	pthread_mutex_lock(info->eat_mut);
	*info->may_eat += 1;
	pthread_mutex_unlock(info->eat_mut);
}

void	next_task(t_phinfo *info, int id, int count)
{
	if (info->ph_status == THINKING)
	{
		eat(info, id, count);
		print_msg(info, "is eating");
		pthread_mutex_unlock(info->ph_mut);
		isleep(info, info->params[TTEAT]);
	}
	else if (info->ph_status == EATING)
	{
		info->ph_status = SLEEPING;
		print_msg(info, "is sleeping");
		pthread_mutex_unlock(info->ph_mut);
		isleep(info, info->params[TTEEP]);
	}
	else if (info->ph_status == SLEEPING)
	{
		info->ph_status = THINKING;
		print_msg(info, "is thinking");
		pthread_mutex_unlock(info->ph_mut);
	}
}

void	philosophate(t_phinfo *info)
{
	pthread_mutex_lock(info->ph_mut);
	pthread_mutex_unlock(info->ph_mut);
	if (info->last_meal.tv_sec == 0)
		gettimeofday(&info->last_meal, NULL);
	if (info->ph_id % 2)
		isleep(info, info->params[TTEAT]);
	while (get_sim_status(info) == ALIVE)
	{
		pthread_mutex_lock(info->ph_mut);
		next_task(info, info->ph_id, info->params[PHILS]);
	}
}

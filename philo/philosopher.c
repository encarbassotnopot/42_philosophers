/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/13 16:42:13 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_phinfo *info, char *msg)
{
	struct timeval	tv;

	pthread_mutex_lock(info->print_mut);
	gettimeofday(&tv, NULL);
	printf("[%lu%03lu] %d %s\n", tv.tv_sec, tv.tv_usec / 1000, info->ph_id,
		msg);
	pthread_mutex_unlock(info->print_mut);
}

void	next_task(t_phinfo *info)
{
	if (info->ph_status == THINKING)
	{
		info->ph_status = EATING;
		print_msg(info, "is eating");
		usleep(info->params[TTEAT] * 1000);
		info->ate++;
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
	info->ph_status = THINKING;
	while (*info->sim_status == ALIVE)
	{
		next_task(info);
	}
}

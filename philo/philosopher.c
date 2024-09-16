/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/16 15:44:41 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	next_task(t_phinfo *info)
{
	if (info->ph_status == THINKING)
	{
		info->ph_status = EATING;
		gettimeofday(&info->last_meal, NULL);
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
	if (info->last_meal.tv_sec == 0)
		gettimeofday(&info->last_meal, NULL);
	info->ph_status = THINKING;
	while (*info->sim_status == ALIVE)
	{
		next_task(info);
	}
}

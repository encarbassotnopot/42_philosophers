/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:35 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/26 18:11:04 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Compares 2 timevals and returns -1, 0 or 1 if the first time is older,
 * equal to or newer than the second one.
 */
int	time_diff(struct timeval *since, struct timeval *until)
{
	if (since->tv_sec < until->tv_sec)
		return (-1);
	if (since->tv_sec > until->tv_sec)
		return (1);
	if (since->tv_usec < until->tv_usec)
		return (-1);
	if (since->tv_usec > until->tv_usec)
		return (1);
	return (0);
}

/**
 * Subtracts the given ammout of ms to the timeval struct pointed by tv
 */
void	time_subt(struct timeval *tv, int ms)
{
	int	usec;

	usec = (tv->tv_usec - ((ms % 1000) * 1000)) % 1000000;
	if (usec < 0)
	{
		usec += 1000000;
		tv->tv_sec -= 1;
	}
	tv->tv_usec = usec;
	tv->tv_sec -= ms / 1000;
}

void	print_msg(t_phinfo *info, char *msg)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(info->print_mut);
	printf("[%lu%03lu] %d %s\n", tv.tv_sec, tv.tv_usec / 1000, info->ph_id,
		msg);
	pthread_mutex_unlock(info->print_mut);
}

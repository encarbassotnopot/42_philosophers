/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:35 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/07 12:40:49 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Adds the given ammout of ms to the timeval struct pointed by tv
 */
void	time_add(struct timeval *tv, int ms)
{
	long	usec;

	usec = (tv->tv_usec + ms * 1000);
	if (usec > 1000000)
	{
		tv->tv_sec += usec / 1000000;
		usec %= 1000000;
	}
	tv->tv_usec = usec;
}

/**
 * Subtracts the given ammout of ms to the timeval struct pointed by tv
 */
void	time_subt(struct timeval *tv, int ms)
{
	long	usec;

	usec = (tv->tv_usec - ((ms % 1000) * 1000)) % 1000000;
	if (usec < 0)
	{
		usec += 1000000;
		tv->tv_sec -= 1;
	}
	tv->tv_usec = usec;
	tv->tv_sec -= ms / 1000;
}

/**
 * Returns the time difference between two timevals in ms.
 * [!] No overflow check
 */
long	time_diff(struct timeval *since, struct timeval *until)
{
	long	diff;

	diff = (until->tv_sec - since->tv_sec) * 1000 * 1000;
	diff += until->tv_usec;
	diff -= since->tv_usec;
	return (diff);
}

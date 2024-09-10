/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/10 12:52:44 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philosophate(t_phinfo *info)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("[%lu%03lu] i'm philo %d\n", tv.tv_sec, tv.tv_usec/1000, *times);
	free(times);
	while (info->*simstatus != EXITED)
	{
		
	}
}

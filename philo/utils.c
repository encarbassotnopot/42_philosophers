/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:35 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/07 12:39:40 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_phinfo *info, char *msg)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(info->print_mut);
	printf("[%lu%03lu] %d %s\n", tv.tv_sec, tv.tv_usec / 1000, info->ph_id,
		msg);
	pthread_mutex_unlock(info->print_mut);
}

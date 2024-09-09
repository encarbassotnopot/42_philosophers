/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/09 18:07:27 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philosophate(int *times)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("[%lu%03lu] i'm philo %d\n", tv.tv_sec, tv.tv_usec/1000, *times);
	free(times);
}

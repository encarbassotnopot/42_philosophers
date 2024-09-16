/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:35 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/16 13:16:57 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

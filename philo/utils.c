/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:11:35 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/08 12:11:58 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_phinfo *info, char *msg)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (get_sim_status(info) != ALIVE)
		return ;
	pthread_mutex_lock(info->print_mut);
	printf("[%li] %d %s\n", time_diff(info->start_time, &tv) / 1000,
		info->ph_id, msg);
	pthread_mutex_unlock(info->print_mut);
}

int	parse_input(int argc, char **argv, int params[])
{
	int	err;

	err = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of args.\n");
		return (1);
	}
	params[4] = 0;
	while (--argc > 0)
	{
		if (!ft_isonlynumstr(argv[argc]))
		{
			printf("Error: Non numeric argument.\n");
			return (1);
		}
		params[argc - 1] = ft_raw_atoi(argv[argc]);
		if (!params[argc - 1] && errno == ERANGE)
		{
			printf("Error: Overflow detected.\n");
			return (1);
		}
	}
	return (0);
}

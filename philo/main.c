/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:11:54 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/09 12:45:39 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	int	params[5];
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of args.\nUsage: "
				"%s number_of_philosophers time_to_die time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]\n",
				argv[0]);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!ft_isonlynumstr(argv[i]))
		{
			printf("Error: Non numeric argument.\nUsage: "
					"%s number_of_philosophers time_to_die time_to_eat time_to_sleep "
					"[number_of_times_each_philosopher_must_eat]\n",
					argv[0]);
			return (1);
		}
		params[i - 1] = ft_raw_atoi(argv[i]);
		if(!params[i - 1] && errno == ERANGE)
		{
			printf("Error: Overflow detected.\nUsage: "
					"%s number_of_philosophers time_to_die time_to_eat time_to_sleep "
					"[number_of_times_each_philosopher_must_eat]\n",
					argv[0]);
			return (1);
		}
	}
}

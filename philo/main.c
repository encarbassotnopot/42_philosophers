/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:11:54 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/16 13:02:23 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	cleanup(pthread_t **threads, pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	/*while ((*forks) + ++i)*/
	/*	pthread_mutex_destroy(forks[i]);*/
	free(*threads);
	free(*forks);
}

t_phinfo	*info_init(int *params, int *sim_status, pthread_mutex_t *forks,
		pthread_mutex_t *print_mut)
{
	t_phinfo	*infos;
	int			i;

	infos = ft_calloc(params[PHILS] + 1, sizeof(t_phinfo));
	if (!infos)
		return (NULL);
	i = -1;
	while (++i < params[PHILS])
	{
		infos[i].sim_status = sim_status;
		infos[i].ph_id = i;
		infos[i].ph_status = THINKING;
		infos[i].params = params;
		infos[i].last_meal = (struct timeval) {0, 0};
		infos[i].forks = forks;
		infos[i].print_mut = print_mut;
	}
	return (infos);
}

int	main(int argc, char **argv)
{
	int				params[5];
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mut;
	int				i;
	t_phinfo		*infos;
	int				sim_status;

	pthread_mutex_init(&print_mut, NULL);
	sim_status = ALIVE;
	if (parse_input(argc, argv, params))
	{
		printf("usage: %s number_of_philosophers time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
				argv[0]);
		return (1);
	}
	threads = ft_calloc(params[PHILS] + 1, sizeof(pthread_t));
	forks = ft_calloc(params[PHILS] + 1, sizeof(pthread_mutex_t));
	infos = info_init(params, &sim_status, forks, &print_mut);
	if (!threads || !forks || !infos)
	{
		free(threads);
		free(forks);
		return (1);
	}
	printf("num %d, die %d, eat %d, sleep %d, times %d\n", params[0], params[1],
		params[2], params[3], params[4]);
	i = -1;
	while (++i < params[PHILS])
	{
		if (pthread_create(&threads[i], NULL, (void *)*philosophate,
				(void *)&infos[i]) || pthread_mutex_init(&forks[i], NULL))
		{
			cleanup(&threads, &forks);
			return (1);
		}
	}
	i = -1;
	while (++i < params[PHILS])
	{
		if (pthread_join(threads[i], NULL))
		{
			cleanup(&threads, &forks);
			return (1);
		}
	}
	cleanup(&threads, &forks);
}

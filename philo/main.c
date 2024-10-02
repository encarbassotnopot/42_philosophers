/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:11:54 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/02 15:05:14 by ecoma-ba         ###   ########.fr       */
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

void	cleanup(pthread_t *threads, t_winfo *winfo)
{
	int	i;

	i = -1;
	free(threads);
	free(winfo->forks);
	free(winfo->phinfos);
}

t_phinfo	*phinfo_init(t_winfo *winfo)
{
	t_phinfo	*infos;
	int			i;

	infos = ft_calloc(winfo->params[PHILS] + 1, sizeof(t_phinfo));
	if (!infos)
		return (NULL);
	i = -1;
	while (++i < winfo->params[PHILS])
	{
		infos[i].sim_status = &winfo->sim_status;
		infos[i].ph_id = i;
		infos[i].ph_status = THINKING;
		infos[i].params = winfo->params;
		infos[i].may_eat = &winfo->may_eat;
		infos[i].last_meal = (struct timeval){0, 0};
		infos[i].forks = winfo->forks;
		infos[i].eat_mut = &winfo->eat_mut;
		infos[i].sim_mut = &winfo->sim_mut;
		infos[i].print_mut = &winfo->print_mut;
		infos[i].ph_mut = &winfo->ph_muts[i];
	}
	return (infos);
}

int	run_threads(t_winfo *winfo, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < winfo->params[PHILS])
	{
		pthread_mutex_init(&winfo->forks[i], NULL);
		pthread_mutex_init(&winfo->ph_muts[i], NULL);
		pthread_mutex_lock(&winfo->ph_muts[i]);
		pthread_create(&threads[i], NULL, (void *)*philosophate,
			(void *)&winfo->phinfos[i]);
	}
	i = -1;
	while (++i < winfo->params[PHILS])
		pthread_mutex_unlock(&winfo->ph_muts[i]);
	pthread_create(&threads[i], NULL, (void *)*necromancer, (void *)winfo);
	i = -1;
	while (++i < winfo->params[PHILS] + 1)
		pthread_join(threads[i], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_winfo		winfo;
	pthread_t	*threads;
	int			params[5];

	pthread_mutex_init(&winfo.print_mut, NULL);
	pthread_mutex_init(&winfo.eat_mut, NULL);
	pthread_mutex_init(&winfo.sim_mut, NULL);
	winfo.sim_status = ALIVE;
	winfo.params = params;
	if (parse_input(argc, argv, params))
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
				"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
				argv[0]);
		return (1);
	}
	winfo.may_eat = params[PHILS] - 1;
	threads = ft_calloc(params[PHILS] + 1, sizeof(pthread_t));
	winfo.forks = ft_calloc(params[PHILS], sizeof(pthread_mutex_t));
	winfo.ph_muts = ft_calloc(params[PHILS], sizeof(pthread_mutex_t));
	winfo.phinfos = phinfo_init(&winfo);
	if (!threads || !winfo.forks || !winfo.ph_muts || !winfo.phinfos)
	{
		free(threads);
		free(winfo.forks);
		free(winfo.ph_muts);
		free(winfo.phinfos);
		return (1);
	}
	printf("num %d, die %d, eat %d, sleep %d, times %d\n", params[0], params[1],
		params[2], params[3], params[4]);
	run_threads(&winfo, threads);
	/*cleanup(threads, &winfo);*/
}

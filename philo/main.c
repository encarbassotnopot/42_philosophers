/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:11:54 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/08 12:11:46 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(pthread_t *threads, t_winfo *winfo)
{
	int	i;

	i = -1;
	free(threads);
	free(winfo->forks);
	free(winfo->phinfos);
	free(winfo->ph_muts);
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
		infos[i].start_time = &winfo->start_time;
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
	gettimeofday(&winfo->start_time, NULL);
	while (++i < winfo->params[PHILS])
		pthread_mutex_unlock(&winfo->ph_muts[i]);
	pthread_create(&threads[i], NULL, (void *)*necromancer, (void *)winfo);
	i = -1;
	while (++i < winfo->params[PHILS] + 1)
		pthread_join(threads[i], NULL);
	return (0);
}

void	gen_winfo(t_winfo *winfo, pthread_t **threads, int *params)
{
	pthread_mutex_init(&winfo->print_mut, NULL);
	pthread_mutex_init(&winfo->eat_mut, NULL);
	pthread_mutex_init(&winfo->sim_mut, NULL);
	winfo->sim_status = ALIVE;
	winfo->params = params;
	winfo->may_eat = params[PHILS] - 1;
	*threads = ft_calloc(params[PHILS] + 1, sizeof(pthread_t));
	winfo->forks = ft_calloc(params[PHILS], sizeof(pthread_mutex_t));
	winfo->ph_muts = ft_calloc(params[PHILS], sizeof(pthread_mutex_t));
	winfo->phinfos = phinfo_init(winfo);
}

int	main(int argc, char **argv)
{
	t_winfo		winfo;
	pthread_t	*threads;
	int			params[5];

	if (parse_input(argc, argv, params))
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	gen_winfo(&winfo, &threads, params);
	if (!threads || !winfo.forks || !winfo.ph_muts || !winfo.phinfos)
	{
		cleanup(threads, &winfo);
		return (1);
	}
	run_threads(&winfo, threads);
	cleanup(threads, &winfo);
}

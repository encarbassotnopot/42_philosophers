/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:13:55 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/10/07 13:07:03 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include "libft.h"
# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# define PHILS 0
# define TTDIE 1
# define TTEAT 2
# define TTEEP 3
# define MEALS 4
# define DEAD 0
# define ALIVE 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4

typedef struct s_phinfo
{
	int				*sim_status;
	int				ph_id;
	int				ph_status;
	int				ate;
	int				*may_eat;
	int				*params;
	struct timeval	last_meal;
	struct timeval	*start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_mut;
	pthread_mutex_t	*sim_mut;
	pthread_mutex_t	*print_mut;
	pthread_mutex_t	*ph_mut;
}					t_phinfo;
typedef struct s_winfo
{
	int				sim_status;
	int				may_eat;
	int				*params;
	struct timeval	start_time;
	t_phinfo		*phinfos;
	pthread_mutex_t	eat_mut;
	pthread_mutex_t	sim_mut;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	*ph_muts;
	pthread_mutex_t	*forks;
}					t_winfo;
void				philosophate(t_phinfo *info);
void				print_msg(t_phinfo *info, char *msg);
void				time_add(struct timeval *tv, int ms);
void				time_subt(struct timeval *tv, int ms);
long				time_diff(struct timeval *since, struct timeval *until);
void				necromancer(t_winfo *w);
#endif

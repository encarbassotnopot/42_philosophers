/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:13:55 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/16 13:24:36 by ecoma-ba         ###   ########.fr       */
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
# define MAY_EAT 5
typedef struct
{
	int				*sim_status;
	int				ph_id;
	int				ph_status;
	int				ate;
	int				*params;
	struct timeval	last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mut;
}					t_phinfo;
void				philosophate(t_phinfo *info);
void				print_msg(t_phinfo *info, char *msg);
int					time_diff(struct timeval *since, struct timeval *until);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:13:55 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/10 12:52:48 by ecoma-ba         ###   ########.fr       */
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
# define RUNNING 0
# define EXITED 1
typedef struct
{
	int				*sim_status;
	int				ph_id;
	int				ph_status;
	int				ate;
	int				params[5];
	pthread_mutex_t	*forks;
}					t_phinfo;
void				philosophate(int *times);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:13:55 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/09 18:25:19 by ecoma-ba         ###   ########.fr       */
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
# define MEALS 4
// TODO: implementar struct de paràmetres: status del programa general,
// id de cada philosopher, tempos donats com arguments i gestió de forquilles
void philosophate(int *times);
#endif

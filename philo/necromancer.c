/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   necromancer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:16:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/09/16 13:13:19 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophate(t_phinfo **philos, int *params)
{
	int		i;
	int		ate_enough;
	timeval	tv;

	i = -1;
	while (philos[0]->sim_status == ALIVE)
	{
		ate_enough = 1;
		while (philos[++i])
		{
			if (mealsphilos[i]->ate < params[MEALS] && params[MEALS])
				ate_enough = 0;

		}
	}
}

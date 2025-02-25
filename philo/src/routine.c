/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/25 11:37:53 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_diff(struct timeval *start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start->tv_sec) * 1000;
	diff += (now.tv_usec - start->tv_usec) / 1000;
	return (diff);
}

int	dead_or_alive(t_simulation *simulation, t_philo *philo)
{
	if (simulation->param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = DEAD;
		pr_s(get_diff(&simulation->t0_simulation),
			philo, COLOR_RED PRINT_DEAD C_R);
		simulation->status = OFF;
		return (DEAD);
	}
	return (ALIVE);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*simulation;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	while (philo->simulation->status == ON)
	{	
		if (dead_or_alive(simulation, philo) == ALIVE)
		{
			if (philo->activity == THINK)
				think(simulation, philo);
			else if (philo->activity == EAT)
				eat(simulation, philo);
			else if (philo->activity == SLEEP)
				sleeep(simulation, philo);
		}
		else
			break ;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/21 11:20:06 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief calculate the diff between now and the start parameter 
/// @param start starting time (T0)
/// @return diff in millisecond since time T0 and now
long	get_diff(struct timeval *start)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - start->tv_sec) * 1000;
	diff += (now.tv_usec - start->tv_usec) / 1000;
	return (diff);
}

/// @brief check if the philo is dead or alive comparing time passed since last meal
/// @param param struct needed for time to dead to compare with last meal
/// @param philo struct + indication WHICH philo we are talking about
/// @return 0 dead | 1 alive
int	dead_or_alive(t_simulation *simulation, t_philo *philo)
{
	if (simulation->param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = DEAD;
		print_philosopher_state(get_diff(&simulation->t0_simulation), philo, PRINT_DEAD);
		simulation->status = OFF;
		return (DEAD);
	}
	return (ALIVE);
}

/// @brief start activity by calling the right function,
/// @param arg need to pass by arg and cast in the function -> arg = philo
/// @return (void *) determined by create_pthread
void	*routine(void *arg)
{
	t_philo 		*philo;
	t_simulation	*simulation;

	philo = (t_philo *)arg;// cast
	simulation = philo->simulation;// l'adresse simulation est maintenant la meme que philo->simulation
	while (philo->simulation->status == ON)
	{	
		// if EVERYONE ARE ALIVE ???
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/31 11:02:56 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (simulation->status == OFF)
		printf("Status == OFF | Philo n°%i, hahahaha il est mort avant moi !\n", philo->id_philo);
	// free_malloc(simulation);
	return (NULL);
}
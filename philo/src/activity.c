/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/31 11:28:41 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
// milliseconds since the beginning of their last meal or the beginning of the sim-
// ulation, they die.
/// @brief print EAT_state in term and start timer ... when time out, philo go to sleep
/// @param param struct need for time to eat
/// @param philo struct need for using the right philo
void	eat(t_simulation *simulation, t_philo *philo)
{
	int right_neighbour;
	if (philo->id_philo == 1)
		right_neighbour = simulation->param->nb_philo - 1;// philo de droite == dernier philo
	else
		right_neighbour = philo->id_philo - 2;// philo de droite
	if (simulation->param->times_each_philo_must_eat == NO_PARAM ||
		simulation->philosophers->meals_eaten <= simulation->param->times_each_philo_must_eat) // check repas en trop
	{
		pthread_mutex_lock(&simulation->philosophers[right_neighbour].left_fork);
		if (dead_or_alive(simulation, philo) == ALIVE)
		{
			pthread_mutex_lock(&philo->left_fork);
			print_philosopher_state(get_diff(&simulation->t0_simulation), philo, TAKING_FORK);
			print_philosopher_state(get_diff(&simulation->t0_simulation), philo, EATING);
			gettimeofday(&philo->last_meal, NULL);
			usleep(simulation->param->t_eat * 1000);
			pthread_mutex_unlock(&philo->left_fork);
			if (simulation->param->times_each_philo_must_eat != NO_PARAM)
				philo->meals_eaten++;
			philo->activity = SLEEP;
		}
		pthread_mutex_unlock(&simulation->philosophers[right_neighbour].left_fork);
	}
	else// assez mange, end of game without dead
		simulation->status = OFF;
}

/// @brief print SLEEP_state in the term and start timer. when time out, philo start thinking
/// @param param need for time to sleep
/// @param philo need for using the right philo
void	sleeep(t_simulation *simulation, t_philo *philo)
{
	print_philosopher_state(get_diff(&simulation->t0_simulation), philo, SLEEPING);
	usleep(simulation->param->t_sleep * 1000);
	philo->activity = THINK; 
}

/// @brief print THINK_stat in the term and ...
/// @param philo need for using the right philo
void	think(t_simulation *simulation, t_philo *philo)
{
    print_philosopher_state(get_diff(&simulation->t0_simulation), philo, THINKING);
	philo->activity = EAT; 
}


/// @brief print in the term > timestamp since start of simulation, wich philo, what he does
/// @param timestamp_in_ms to print the time since the begin of the simulation
/// @param philo to use the right philo and the right data stock in his struct
/// @param state_message to print the right activity, macro in philo.h
void print_philosopher_state(long timestamp_in_ms, t_philo *philo, char *state_message)
{
	
	if (philo->simulation->status == ON)// pourquoi ca ne suffit pas pour eviter lecriture lorsque le status est OFF ?
	{
		pthread_mutex_lock(&philo->simulation->print_mutex);
		if (philo->simulation->status == ON)
			printf("%9ld \tPhilo n°%-7d %s\n", timestamp_in_ms, philo->id_philo, state_message);
		pthread_mutex_unlock(&philo->simulation->print_mutex);
	}
}
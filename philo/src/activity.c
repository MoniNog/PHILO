/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/08 19:13:27 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief print EAT_state in term and start timer ... when time out, philo go to sleep
/// @param param struct need for time to eat
/// @param philo struct need for using the right philo
void	eat(t_simulation *simulation, t_param *param, t_philo *philo)
{
	print_philosopher_state(get_diff(&simulation->t0_simulation), philo, EATING);
	gettimeofday(&philo->last_meal, NULL);// ??
	usleep(param->t_eat * 1000);
	philo->activity = 3;
}

/// @brief print SLEEP_state in the term and start timer. when time out, philo start thinking
/// @param param need for time to sleep
/// @param philo need for using the right philo
void	sleeep(t_simulation *simulation, t_param *param, t_philo *philo)
{
	print_philosopher_state(get_diff(&simulation->t0_simulation), philo, SLEEPING);
	usleep(param->t_sleep * 1000);
	philo->activity = 1; 
}
// time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
// milliseconds since the beginning of their last meal or the beginning of the sim-
// ulation, they die.

/// @brief print THINK_stat in the term and ...
/// @param philo need for using the right philo
void	think(t_simulation *simulation, t_philo *philo)
{
    print_philosopher_state(get_diff(&simulation->t0_simulation), philo, THINKING);
	usleep(10 * 1000);// FAUX
	philo->activity = 2; 
	// TODO : pick up fork 
}

/// @brief print in the term > timestamp since start of simulation, wich philo, what he does
/// @param timestamp_in_ms to print the time since the begin of the simulation
/// @param philo to use the right philo and the right data stock in his struct
/// @param state_message to print the right activity, macro in philo.h
void print_philosopher_state(long timestamp_in_ms, t_philo *philo, const char *state_message)
{
    struct timeval t0_simulation;
    gettimeofday(&t0_simulation, NULL);

    // pthread_mutex_lock(&print_mutex);
    printf("%9ld \tPhilo n°%-7d %s\n", timestamp_in_ms, philo->id_philo, state_message);
    // pthread_mutex_unlock(&print_%mutex);
}
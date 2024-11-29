/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2024/11/29 09:00:57 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_param *param, t_philo *philo)
{
	print_philosopher_state(get_diff(&philo->t0_simulation), philo, EATING);
	// printf("timestamp : %li\t\tphilo number %i\t\tis eating\n", get_diff(&philo->t0_simulation), philo->id_philo);
	gettimeofday(&philo->last_meal, NULL);
	usleep(param->t_eat * 1000);
	philo->activity = 3;
}

void	sleeep(t_param *param, t_philo *philo)
{
	print_philosopher_state(get_diff(&philo->t0_simulation), philo, SLEEPING);
	//printf("timestamp : %li\t\tphilo number %i\t\tis sleeping\n", get_diff(&philo->t0_simulation), philo->id_philo);
	usleep(param->t_sleep * 1000);
	philo->activity = 1; 
}

void	think(t_philo *philo)
{
    print_philosopher_state(get_diff(&philo->t0_simulation), philo, THINKING);
	// printf("timestamp : %li\t\tphilo number %i\t\tis thinking\n", get_diff(&philo->t0_simulation), philo->id_philo);
	usleep(10 * 1000);
	philo->activity = 2; 
}

void print_philosopher_state(long timestamp_in_ms, t_philo *philo, const char *state_message)
{
    struct timeval t0_simulation;
    gettimeofday(&t0_simulation, NULL);

    // pthread_mutex_lock(&print_mutex);
    printf("%9ld \tPhilo n°%-7d %s\n", timestamp_in_ms, philo->id_philo, state_message);
    // pthread_mutex_unlock(&print_%mutex);
}
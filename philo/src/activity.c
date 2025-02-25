/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/24 11:05:14 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	eat_loop(t_simulation *simulation, t_philo *philo, int right_neighbour)
{
	while (philo->state_fork == LOCKED)
	{
		usleep(10);
		if (dead_or_alive(simulation, philo) == DEAD)
			break;
	}
	pthread_mutex_lock(&simulation->philosophers[right_neighbour].left_fork);
	simulation->philosophers[right_neighbour].state_fork = LOCKED;
	if (dead_or_alive(simulation, philo) == ALIVE)
	{
		pthread_mutex_lock(&philo->left_fork);
		philo->state_fork = LOCKED;
		PRINT(get_diff(&simulation->t0_simulation), philo, TAKING_FORK);
		PRINT(get_diff(&simulation->t0_simulation), philo, EATING);
		gettimeofday(&philo->last_meal, NULL);
		usleep(simulation->param->t_eat * 1000);
		philo->state_fork = UNLOCKED;
		pthread_mutex_unlock(&philo->left_fork);
		if (simulation->param->times_each_philo_must_eat != NO_PARAM)
			philo->meals_eaten++;
		philo->activity = SLEEP;
	}
	pthread_mutex_unlock(&simulation->philosophers[right_neighbour].left_fork);
	simulation->philosophers[right_neighbour].state_fork = UNLOCKED;
}

void	eat(t_simulation *simulation, t_philo *philo)
{
	int	right_neighbour;
	if (philo->id_philo == 1)
		right_neighbour = simulation->param->nb_philo - 1;
	else
		right_neighbour = philo->id_philo - 2;// philo de droite
	if (simulation->param->times_each_philo_must_eat == NO_PARAM ||
		simulation->philosophers->meals_eaten <=
		simulation->param->times_each_philo_must_eat)
		eat_loop(simulation, philo, right_neighbour);
	else
		simulation->status = OFF;
}

void	sleeep(t_simulation *simulation, t_philo *philo)
{
	print_philosopher_state(get_diff(&simulation->t0_simulation), philo, 
		SLEEPING);
	usleep(simulation->param->t_sleep * 1000);
	philo->activity = THINK; 
}

void	think(t_simulation *simulation, t_philo *philo)
{
    print_philosopher_state(get_diff(&simulation->t0_simulation), philo,
		THINKING);
	philo->activity = EAT; 
}

void	print_philosopher_state(long timestamp_in_ms, t_philo *philo, 
	char *state_message)
{
	if (philo->simulation->status == ON)
	{
		pthread_mutex_lock(&philo->simulation->print_mutex);
		if (philo->simulation->status == ON)
			printf("%9ld \tPhilo n°%-7d %s\n", timestamp_in_ms,
				philo->id_philo, state_message);
		pthread_mutex_unlock(&philo->simulation->print_mutex);
	}
}

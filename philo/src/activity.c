/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 15:53:45 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_loop(t_simulation *simulation, t_philo *philo, int right_neighbour)
{
	pthread_mutex_lock(&simulation->philosophers[right_neighbour].left_fork);
	simulation->philosophers[right_neighbour].state_fork = LOCKED;
	pr_s(get_diff(&simulation->t0_simulation), philo, COLOR_YELLOW 
		TAKING_FORK C_R);
	if (dead_or_alive(simulation, philo) == ALIVE)
	{
		pthread_mutex_lock(&philo->left_fork);
		philo->state_fork = LOCKED;
		pr_s(get_diff(&simulation->t0_simulation), philo, COLOR_YELLOW
			TAKING_FORK C_R);
		pr_s(get_diff(&simulation->t0_simulation), philo, COLOR_GR EATING C_R);
		gettimeofday(&philo->last_meal, NULL);
		usleep(simulation->param->t_eat * 1000);
		philo->state_fork = UNLOCKED;
		pthread_mutex_unlock(&philo->left_fork);
		if (simulation->param->times_each_philo_must_eat != NO_PARAM)
			philo->meals_eaten++;
		philo->activity = SLEEP;
	}
	simulation->philosophers[right_neighbour].state_fork = UNLOCKED;
	pthread_mutex_unlock(&simulation->philosophers[right_neighbour].left_fork);
}

void	eat(t_simulation *simulation, t_philo *philo)
{
	int	right_neighbour;
	int	left_neighbour;

	if (philo->id_philo == 1)
	{
		right_neighbour = simulation->param->nb_philo - 1;
		left_neighbour = simulation->param->nb_philo + 1;
	}
	else
	{
		right_neighbour = philo->id_philo - 2;
		left_neighbour = philo->id_philo;//segv
	}	
	if (simulation->param->times_each_philo_must_eat == NO_PARAM
		|| simulation->philosophers->meals_eaten
		<= simulation->param->times_each_philo_must_eat)
		{	
			while (philo->state_fork == LOCKED &&
				simulation->philosophers[right_neighbour].state_fork == LOCKED)
			{
				usleep(1);
				if (dead_or_alive(simulation, philo) == DEAD)
					break ;
			}
			if (simulation->philosophers[right_neighbour].meals_eaten >= philo->meals_eaten || simulation->philosophers[left_neighbour].meals_eaten <= philo->meals_eaten)
					eat_loop(simulation, philo, right_neighbour);
		}
	else
		simulation->status = OFF;
}

void	sleeep(t_simulation *simulation, t_philo *philo)
{
	pr_s(get_diff(&simulation->t0_simulation), philo,
		COLOR_BLUE SLEEPING C_R);
	usleep(simulation->param->t_sleep * 1000);
	philo->activity = THINK;
}

void	think(t_simulation *simulation, t_philo *philo)
{
	pr_s(get_diff(&simulation->t0_simulation), philo,
		COLOR_GREY THINKING C_R);
	philo->activity = EAT;
}

void	pr_s(long timestamp_in_ms, t_philo *philo,
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

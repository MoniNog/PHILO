/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:10:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 20:46:05 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_loop(t_simulation *simulation, t_philo *philo, int nb_right_neighb)
{
	pthread_mutex_lock(&simulation->philosophers[nb_right_neighb].left_fork);
	simulation->philosophers[nb_right_neighb].state_fork = LOCKED;
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
	simulation->philosophers[nb_right_neighb].state_fork = UNLOCKED;
	pthread_mutex_unlock(&simulation->philosophers[nb_right_neighb].left_fork);
}

void	check_fork(t_philo *philo, t_simulation *sim, int right, int left)
{
	while (philo->state_fork == LOCKED
		&& sim->philosophers[right].state_fork == LOCKED)
	{
		usleep(1);
		if (dead_or_alive(sim, philo) == DEAD)
			break ;
	}
	if (sim->philosophers[right].meals_eaten >= philo->meals_eaten
		|| sim->philosophers[left].meals_eaten <= philo->meals_eaten)
		eat_loop(sim, philo, right);
}

void	eat(t_simulation *simulation, t_philo *philo)
{
	int	nb_right_neighb;
	int	nb_left_neighbour;

	if (philo->id_philo == 1)
	{
		nb_right_neighb = simulation->param->nb_philo - 1;
		nb_left_neighbour = 1;
	}
	else
	{
		nb_right_neighb = philo->id_philo - 2;
		nb_left_neighbour = philo->id_philo;
	}
	if (simulation->param->times_each_philo_must_eat == NO_PARAM
		|| simulation->philosophers->meals_eaten
		<= simulation->param->times_each_philo_must_eat)
		check_fork(philo, simulation, nb_right_neighb, nb_left_neighbour);
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

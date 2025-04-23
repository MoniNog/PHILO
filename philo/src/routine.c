/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 15:16:02 by monoguei         ###   ########.fr       */
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
		pthread_mutex_lock(&simulation->status_mutex);
		simulation->status = OFF;// proteger modification avec mutex
		pthread_mutex_unlock(&simulation->status_mutex);
		return (DEAD);
	}
	return (ALIVE);
}

int ft_check_status(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->status_mutex);
	if (simulation->status == ON)
	{
		pthread_mutex_unlock(&simulation->status_mutex);
		return ON;
	}
	else
	{
		pthread_mutex_unlock(&simulation->status_mutex);
		return OFF;
	}
	
}
void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*simulation;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	while (ft_check_status(simulation) == ON)// while (ft_check status whit mutex)
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

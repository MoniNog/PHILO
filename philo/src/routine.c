/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:54:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/23 20:38:53 by monoguei         ###   ########.fr       */
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
		simulation->status = OFF;
		pthread_mutex_unlock(&simulation->status_mutex);
		return (DEAD);
	}
	return (ALIVE);
}

int	ft_check_status(t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->status_mutex);
	if (simulation->status == ON)
	{
		pthread_mutex_unlock(&simulation->status_mutex);
		return (ON);
	}
	else
	{
		pthread_mutex_unlock(&simulation->status_mutex);
		return (OFF);
	}
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*simulation;

	philo = (t_philo *)arg;
	simulation = philo->simulation;
	while (ft_check_status(simulation) == ON)
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

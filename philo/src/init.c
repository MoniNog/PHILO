/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/07 10:37:11 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_philo(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->param->nb_philo)
	{
		simulation->philosophers[i].id_philo = i + 1;
		simulation->philosophers[i].activity = THINK;
		simulation->philosophers[i].simulation = simulation;
		gettimeofday(&simulation->philosophers[i].last_meal, NULL);
		i++;
	}
}

void	init_simulation(t_simulation *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_init(&simulation->print_mutex, NULL);
	gettimeofday(&simulation->t0_simulation, NULL);
	init_philo(simulation);
	simulation->status = 1;
	while (i < simulation->param->nb_philo)
	{
		
		if (simulation->philosophers[i].id_philo % 2 == 1)
			usleep(10);
		pthread_create(simulation->philosophers[i].thread, NULL, routine,
			(void *)&simulation->philosophers[i]);
		if (simulation->param->times_each_philo_must_eat != NO_PARAM)
			simulation->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&simulation->philosophers[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < simulation->param->nb_philo)
	{
		pthread_join(*simulation->philosophers[i].thread, NULL);
		i++;
	}
}

void	create_philo(char **av, t_simulation *simulation)
{
	simulation->param = malloc(sizeof(t_param));
	if (!simulation->param)
		return ;
	simulation->param->nb_philo = atoi(av[1]);
	simulation->param->t_die = atoi(av[2]);
	simulation->param->t_eat = atoi(av[3]);
	simulation->param->t_sleep = atoi(av[4]);
	simulation->philosophers
		= malloc(sizeof(t_philo) * simulation->param->nb_philo);
	if (!simulation->philosophers)
		return ;
}

t_simulation	*create_simulation(char **av)
{
	t_simulation	*simulation;
	int				i;

	if (param_are_valid(av) == TRUE)
	{
		simulation = malloc(sizeof(t_simulation));
		if (!simulation)
			return (NULL);
		i = 0;
		create_philo(av, simulation);
		while (i < simulation->param->nb_philo)
		{
			simulation->philosophers[i].thread = malloc(sizeof(pthread_t));
			if (!simulation->philosophers[i++].thread)
				return (NULL);
		}
		if (av[5] && atoi(av[5]) > 0)
			simulation->param->times_each_philo_must_eat = atoi(av[5]);
		else
			simulation->param->times_each_philo_must_eat = -1;
		return (simulation);
	}
	return (NULL);
}

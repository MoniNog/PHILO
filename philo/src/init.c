/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/22 17:14:18 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief Check if malloc success
/// @param simulation 
/// @return 0 : malloc fail, memory free | 1 : malloc success
int	free_malloc(t_simulation *simulation)
{
	int	i;

	i = 0;
	while(i < simulation->param->nb_philo)
	{
		pthread_mutex_destroy(&simulation->philosophers[i].left_fork);
		free(simulation->philosophers[i].thread);
		i++;
	}
	free(simulation->philosophers);
	free(simulation->param);
	pthread_mutex_destroy(&simulation->print_mutex);
	free(simulation);
	return (0);
}

void init_philo(t_simulation *simulation)
{
	int	i;
	i = 0;
	while (i < simulation->param->nb_philo) // initialisation
	{
		simulation->philosophers[i].id_philo = i + 1;
		simulation->philosophers[i].activity = THINK;//?SLEEP? -> Non car ils commencent par vouloir manger donc THINK
		simulation->philosophers[i].simulation = simulation;
	    gettimeofday(&simulation->philosophers[i].last_meal, NULL); // Initialiser last_meal avec l'heure actuelle
		i++;
	}
}

/// @brief set id philo, init first activity, create the threads, waiting (join ???) INIT THE SIMULATION
/// @param param struct where are the philo's data
/// @brief set T0, 
/// @param simulation 
void init_simulation(t_simulation *simulation)
{
	int			i;

	pthread_mutex_init(&simulation->print_mutex, NULL);
	gettimeofday(&simulation->t0_simulation, NULL);// start simulation at time 0 

	init_philo(simulation);
	simulation->status = 1;
	i = 0;
	while (i < simulation->param->nb_philo) // lancement
	{
		pthread_create(simulation->philosophers[i].thread, NULL, routine, 
			(void *)&simulation->philosophers[i]);
		if (simulation->param->times_each_philo_must_eat != NO_PARAM)
			simulation->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&simulation->philosophers[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < simulation->param->nb_philo) // attente
	{
		pthread_join(*simulation->philosophers[i].thread, NULL);
			i++;
	}
}

/// @brief malloc struct, atoi params and stock them
/// @param av param set in the command line (nb_philo, t_die, t_eat, t_sleep, (times_each_philo_must_eat))
/// @return simulation where are param with the values enter in the command line
t_simulation	*create_simulation(char **av)
{
	t_simulation	*simulation;
	int				i;

	if (param_are_valid(av) == TRUE)
	{
		simulation = malloc(sizeof(t_simulation));
		if (!simulation)
			return NULL;
		simulation->param = malloc(sizeof(t_param));
		if (!simulation->param)
			return NULL;
		simulation->param->nb_philo = atoi(av[1]);
		simulation->param->t_die = atoi(av[2]);
		simulation->param->t_eat = atoi(av[3]);
		simulation->param->t_sleep = atoi(av[4]);
		simulation->philosophers = malloc(sizeof(t_philo) * simulation->param->nb_philo);
		if (!simulation->philosophers)
			return NULL;
		i = 0;
		while (i < simulation->param->nb_philo)
		{
			simulation->philosophers[i].thread = malloc(sizeof(pthread_t));
			if (!simulation->philosophers[i++].thread)
				return NULL;
		}
		if (av[5] && atoi(av[5]) > 0)
			simulation->param->times_each_philo_must_eat = atoi(av[5]);
		else
			simulation->param->times_each_philo_must_eat = -1;
		return (simulation);
	}
	return NULL;
}

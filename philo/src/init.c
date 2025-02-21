/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/21 10:35:20 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief set id philo, init first activity, create the threads, waiting (join ???) INIT THE SIMULATION
/// @param param struct where are the philo's data
/// @brief set T0, 
/// @param simulation 
void init_simulation(t_simulation *simulation)
{
	int			i;

	pthread_mutex_init(&simulation->print_mutex, NULL);

	gettimeofday(&simulation->t0_simulation, NULL);// start simulation at time 0 
	i = 0;
	while (i < simulation->param->nb_philo) // initialisation
	{
		simulation->philosophers[i].id_philo = i + 1;
		simulation->philosophers[i].activity = THINK;//?SLEEP? -> Non car ils commencent par vouloir manger donc THINK
		simulation->philosophers[i].simulation = simulation;
	    gettimeofday(&simulation->philosophers[i].last_meal, NULL); // Initialiser last_meal avec l'heure actuelle
		i++;
	}
	simulation->status = 1;
	i = 0;
	while (i < simulation->param->nb_philo) // lancement
	{
		pthread_create(simulation->philosophers[i].thread, NULL, routine, (void *)&simulation->philosophers[i]);
		if (simulation->param->times_each_philo_must_eat != NO_PARAM)
			simulation->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&simulation->philosophers[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < simulation->param->nb_philo) // attente
		pthread_join(*simulation->philosophers[i++].thread, NULL);
}

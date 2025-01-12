/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/10 12:25:00 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief set id philo, init first activity, create the threads, waiting (join ???) INIT THE SIMULATION
/// @param param struct where are the philo's data
void init_simulation(t_simulation *simulation)
{
	pthread_t	*threads;/// phtread * on essaie comme ca mais possible quon doit changer vers pthread **
	int			i;

	threads = malloc(sizeof(pthread_t) * simulation->param->nb_philo);
	if (!threads)
		return ;

	gettimeofday(&simulation->t0_simulation, NULL);// start simulation at time 0 

	i = 0;
	while (i < simulation->param->nb_philo) // initialisation
	{
		simulation->philosophers[i].id_philo = i + 1;
		simulation->philosophers[i].activity = THINK;//?SLEEP?
		simulation->philosophers[i].simulation = simulation;
	    gettimeofday(&simulation->philosophers[i].last_meal, NULL); // Initialiser last_meal avec l'heure actuelle
		i++;
	}



	i = 0;
	while (i < simulation->param->nb_philo) // lancement
	{
		pthread_create(&(threads[i]), NULL, routine, (void *)&simulation->philosophers[i]);
		i++;
	}

	write(1, "1\n", 2); // segv

	i = 0;
	while (i < simulation->param->nb_philo) // attente
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

/// @brief check if the philo is dead or alive comparing time passed since last meal
/// @param param struct needed for time to dead to compare with last meal
/// @param philo struct + indication WHICH philo we are talking about
/// @return 0 dead | 1 alive
int	dead_or_alive(t_simulation *simulation, t_param *param, t_philo *philo)
{
	if (param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = 0;
		print_philosopher_state(get_diff(&simulation->t0_simulation), philo, PRINT_DEAD);
		return (0);
	}
	return (1);
}

/// @brief start activity by calling the right function,
/// @param arg need to pass by arg and cast in the function -> arg = philo
/// @return (void *) determined by create_pthread
void	*routine(void *arg)
{
	t_philo 		*philo;
	t_simulation	*simulation;

	philo = (t_philo *)arg;// cast
	simulation = philo->simulation;// l'adresse simulation est maintenant la meme que philo->simulation
	while (philo->activity != DEAD)
	{	
		if (dead_or_alive(simulation, simulation->param, philo) == 1)
		{
			if (philo->activity == THINK)
				think(simulation, philo);
			else if (philo->activity == EAT)
				eat(simulation, simulation->param, philo);
			else if (philo->activity == SLEEP)
				sleeep(simulation, simulation->param, philo);
		}
		else
			philo->activity = DEAD; 
	}
	return (NULL);
}

	// pthread_t	t2;
	// param->philos->id_philo = 1;
	// param->philos->id_philo = 2;
	// pthread_create(&t1, NULL, &routine, param);
	// pthread_create(&t2, NULL, &routine, param);
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
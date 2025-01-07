/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:16:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/01/07 12:12:08 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief set id philo, init first activity, create the threads, waiting (join ???) INIT THE SIMULATION
/// @param param struct where are the philo's data
void initialize_simulation(t_param *param)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t *) * param->nb_philo);

	i = 0;
	while (i < param->nb_philo) // initialisation
	{
		param->philos[i].id_philo = i + 1;
		param->philos[i].param = param;// activite de depart
		param->philos[i].activity = 1;
		i++;
	}

	i = 0;
	while (i < param->nb_philo) // lancement
	{
		pthread_create(thread, NULL, routine, (void *)&param->philos[i]);
		i++;
	}

	i = 0;
	while (i < param->nb_philo) // attente
	{
		pthread_join(thread[i], NULL);
		i++;
	}
}

/// @brief check if the philo is dead or alive comparing time passed since last meal
/// @param param struct needed for time to dead to compare with last meal
/// @param philo struct + indication WHICH philo we are talking about
/// @return 0 dead | 1 alive
int	dead_or_alive(t_param *param, t_philo *philo)
{
	if (param->t_die <= get_diff(&philo->last_meal))
	{
		philo->activity = 0;
		print_philosopher_state(get_diff(&philo->t0_simulation), philo, PRINT_DEAD);
		return (0);
	}
	return (1);
}

/// @brief start activity by calling the right function,
/// @param arg need to pass by arg and cast in the function -> arg = philo
/// @return (void *) determined by create_pthread
void	*routine(void *arg)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)arg;// cast
	param = philo->param;// raccourci, a changer avec la struct_sim
	gettimeofday(&philo->last_meal, NULL); // Initialiser last_meal avec l'heure actuelle	[_] A DEPLACER DANS INITIALIZE_SIMULATION
	gettimeofday(&philo->t0_simulation, NULL);// start simulation at time 0 				[_] A DEPLACER DANS INITIALIZE_SIMULATION
	while (philo->activity != DEAD)
	{	
		if (dead_or_alive(param, philo) == 1)
		{
			if (philo->activity == THINK)
				think(philo);
			else if (philo->activity == EAT)
				eat(param, philo);
			else if (philo->activity == SLEEP)
				sleeep(param, philo);
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
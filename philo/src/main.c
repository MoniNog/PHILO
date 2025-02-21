/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@lausanne42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/02/21 10:41:19 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/// @brief 
/// @param av 
/// @return 0 param are neg | 1 params ARE POS or 0
int param_are_valid(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (atoi(av[i]) < 0)
			return (FALSE);
		else
			i++;
	}
	return (TRUE);
}

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


int main(int ac, char **av)
{
	t_simulation *simulation;

	if (ac == 6 || ac == 5)
	{
		simulation = create_simulation(av);
		if (simulation)
		{
			if (simulation->param->nb_philo == 1)
				printf("\t0\tPhilo n°1\t%s\n\t0\tPhilo n°1\t%s\n\t%s\tPhilo n°1\t%s\n", THINKING, TAKING_FORK, av[2], PRINT_DEAD);
			else
				init_simulation(simulation);
			free_malloc(simulation);
		}
	}
	return 0;
}
